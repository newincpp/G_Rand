#include <iostream>
#include <chrono>
#include "IL/ilut.h"
#include "IL/ilu.h"
#include "IL/il.h"
#include "core.hh"

#include "postProcMaterial.hh"

GRand::Core::Core() : _window(NULL), _state(std::bind(&GRand::Core::_interal_WaitForWindow_, this)), _validState(true) {
}

GRand::Core::~Core() {
    if (_rtt) {
	delete _rtt;
    }
    _scope->join();
    delete _scope;
    glfwDestroyWindow(_window);
    glDeleteBuffers(1, &_renderVbo);
    //glfwTerminate();
}

bool GRand::Core::getStateValidity() {
    return _validState;
}

void GRand::Core::_interal_WaitForWindow_() {
    if (_window) {
	glfwMakeContextCurrent(_window);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_DEPTH_BITS, 32);
	glfwSetKeyCallback(_window, key_callback);
	_state = std::bind(&GRand::Core::_interal_render_, this);
	glewExperimental = GL_TRUE;
	int err;
	if ((err = glewInit()) != GLEW_OK) {
	    std::cout << glewGetErrorString(err) << std::endl;
	}

	GLenum error;
	if((error = ilGetError()) != IL_NO_ERROR) {
	    std::cout << "Error initializing DevIL: " << iluErrorString(error) << std::endl;
	}
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "runing on: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Shading language version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_TEXTURE_2D);

	ilInit();
	ilClearColour(0, 255, 0, 0);
	ilutRenderer(ILUT_OPENGL);

	_postProcessInit();
    }
}

void GRand::Core::_postProcessInit() {
    _genPPvbo();
    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    _rtt = new RenderTexture(viewport[2] - viewport[0], viewport[3] - viewport[1]);
    _postProcessMaterial = new ppMaterial(this, _rtt);
}

void GRand::Core::_genPPvbo() {
    GLfloat vertexArray[8] = {
	-1, -1,
	1, -1,
	-1,  1,
	1,  1,
    };
    glGenBuffers(1, &_renderVbo);
    glBindBuffer(GL_ARRAY_BUFFER, _renderVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GRand::Core::noPostProcess(bool destroy_) {
    if (destroy_) {
	delete _rtt;
	_rtt = 0;
	std::cout << "del" << std::endl;
    }
}

void GRand::Core::_interal_render_() {
    // enable render into texture
    std::chrono::high_resolution_clock::time_point before = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point after;
    if (_rtt) {
	_rtt->bindFramebuffer();
    }
    // draw the elements

    glClear(GL_COLOR_BUFFER_BIT);
#ifdef THREAD_SHOW
    std::cout << "\033[1m";
#endif
    if (_instructionQueue.size()) {
	_instructionQueue.front()();
	_instructionQueue.pop();
    }
    for (std::function<void()>& f : _instructionList) {
#ifdef THREAD_SHOW
	std::cout << "\033[1m";
	f();
	std::cout << "\033[0m";
#else
	f();
#endif
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    if (_rtt) {
	// draw the renderTexture into the screen
	_postProcessMaterial->use();	
	glBindBuffer(GL_ARRAY_BUFFER, _renderVbo);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0); // vertex
	/* better if get from the active camera */
	_rtt->bind(GL_TEXTURE0);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }

    glfwSwapBuffers(_window);
    after = std::chrono::high_resolution_clock::now();
    _rendertime = std::chrono::duration_cast<std::chrono::nanoseconds>(after - before).count();
    glfwPollEvents();
    _validState = !glfwWindowShouldClose(_window);
}

void GRand::Core::_coreLoop() {
    std::cout << "run" << std::endl;
    while (_validState) {
	_state();
    }
}

GRand::Core* GRand::Core::start(const Config& conf_) {
    static bool glfwInititialized;
    if (!glfwInititialized) {
	if (!glfwInit())
	    return NULL; // TODO add log system
	glfwInititialized = true;
    }
    GRand::Core* e = NULL;

    std::mutex m;
    std::thread* t = new std::thread(_exec, &e, &m);
    std::cout << "wait for engine*" << std::endl;

    GLFWmonitor* monitor = NULL;
    if (conf_.fullscreen) { // in case of fullscreen override the conf to get the native one for simplicity
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_DEPTH_BITS, 32);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
    }

    GLFWwindow* w = glfwCreateWindow(conf_.winWidth, conf_.winHeight, conf_.winName.c_str(), monitor, NULL);
    if (!w) {
	std::cout << "failed to create window" << std::endl; // TODO add log system
	glfwTerminate();
	return NULL; 
    }
    m.lock();
    e->_window = w;
    e->_scope = t;
    return e;
}

void GRand::Core::_exec(GRand::Core** e_, std::mutex* m_) {
    *e_ = new Core();
    m_->unlock();
    (*e_)->_coreLoop();
}

void GRand::Core::Config::autoConf(Config& cfg_) {
    cfg_.winWidth = 1280; //  1280 × 720
    cfg_.winHeight = 720;
    cfg_.winName = "default";
    cfg_.fullscreen = false;
}

void GRand::Core::queueIntruction(const std::function<void()>& instruction_) {
    _instructionQueue.push(instruction_); 
}

unsigned long GRand::Core::addPersistantInstruction(const std::function<void()>& instruction_) {
    _instructionList.push_back(instruction_);
    return _instructionList.size() - 1;
}

void GRand::Core::deletePersistantInstruction(unsigned long i_) {
    if (i_ >= _instructionList.size()) {
	return;
    }
    _instructionList[i_] = [](){};
    _instructionQueue.push(std::bind(&::GRand::Core::_rmFunc, this, i_));
}

void GRand::Core::_rmFunc(unsigned long id_) {
    _instructionList.erase(_instructionList.begin() + id_);
}

void GRand::Core::addInputCallback(int key, const std::function<void(void)>& call) {
    _inputMap[key] = call;
}

void GRand::Core::key_callback(GLFWwindow* window, int key, int, int action, int) {
    if (action == GLFW_PRESS) {
	if (key == GLFW_KEY_ESCAPE) {
	    glfwSetWindowShouldClose(window, GL_TRUE);
	}
//	const decltype(_inputMap)::const_iterator i = _inputMap.find(key);
//	if (i != _inputMap.end()) {
//	    i->second();
//	}
    }
}
