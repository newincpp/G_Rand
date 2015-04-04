#include <iostream>
#include "core.hh"

tinyGL::Core::Core() : _window(NULL), _state(std::bind(&tinyGL::Core::_interal_WaitForWindow_, this)), _validState(true) {
}

tinyGL::Core::~Core() {
    glfwDestroyWindow(_window);
    //glfwTerminate();
}

bool tinyGL::Core::getStateValidity() {
    return _validState;
}

void tinyGL::Core::_interal_WaitForWindow_() {
    if (_window) {
	glfwMakeContextCurrent(_window);
	glfwSetKeyCallback(_window, tinyGL::Core::key_callback);
	_state = std::bind(&tinyGL::Core::_interal_render_, this);
    }
}

void tinyGL::Core::_interal_render_() {
	glClear(GL_COLOR_BUFFER_BIT);
	if (_instructionQueue.size()) {
	    _instructionQueue.front()();
	    _instructionQueue.pop();
	}
	glfwSwapBuffers(_window);
	glfwPollEvents();
	_validState = !glfwWindowShouldClose(_window);
}

void tinyGL::Core::_coreLoop() {
    while (_validState) {
	_state();
    }
}

tinyGL::Core* tinyGL::Core::start(const Config& conf_) {
    static bool glfwInititialized;
    if (!glfwInititialized) {
	if (!glfwInit())
	    return NULL; // TODO add log system
	glfwInititialized = true;
    }
    tinyGL::Core* e = NULL;

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

void tinyGL::Core::_exec(tinyGL::Core** e_, std::thread* t_) {
    *e_ = new Core();
    (*e_)->_scope = t_;
    (*e_)->_coreLoop();
}

void tinyGL::Core::Config::autoConf(Config& cfg_) {
    cfg_.winWidth = 1280; //  1280 × 720
    cfg_.winHeight = 720;
    cfg_.winName = "default";
    cfg_.fullscreen = false;
}





void tinyGL::Core::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
	glfwSetWindowShouldClose(window, GL_TRUE);
    }
}
