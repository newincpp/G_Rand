#include <iostream>
#include "IL/ilut.h"
#include "IL/ilu.h"
#include "IL/il.h"
#include "core.hh"

GRand::Core::Core() : _window(NULL), _state(std::bind(&GRand::Core::_interal_WaitForWindow_, this)), _validState(true) {
}

GRand::Core::~Core() {
    glfwDestroyWindow(_window);
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

	GLuint VertexArray;
	glGenVertexArrays(1, &VertexArray);
	glBindVertexArray(VertexArray);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	ilInit();
	ilClearColour(0, 255, 0, 0);
	ilutRenderer(ILUT_OPENGL);
    }
}

void GRand::Core::_interal_render_() {
    glClear(GL_COLOR_BUFFER_BIT);
    if (_instructionQueue.size()) {
	_instructionQueue.front()();
	_instructionQueue.pop();
    }
    for (std::function<void()>& f : _instructionList) {
	f();
    }
    glfwSwapBuffers(_window);
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

    std::thread* t = new std::thread(_exec, &e, t);
    if (!e) {
	std::cout << "wait for engine*" << std::endl;
	while (!e) { } // wierd lock to wait for the construction of the engine...
    }

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
    e->_window = w;
    return e;
}

void GRand::Core::_exec(GRand::Core** e_, std::thread* t_) {
    *e_ = new Core();
    (*e_)->_scope = t_;
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
