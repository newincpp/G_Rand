#include <iostream>
#include "core.hh"

tinyGL::Core::Core() : _window(NULL), _state(std::bind(&tinyGL::Core::_interal_WaitForWindow_, this)), _validState(true) {
}

tinyGL::Core::~Core() {
    glfwTerminate();
    _scope->join();
}

void tinyGL::Core::_interal_WaitForWindow_() {
    if (_window) {
	glfwMakeContextCurrent(_window);
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
    while (_validState)
	_state();
}

tinyGL::Core* tinyGL::Core::start() {
    static bool glfwInititialized;
    if (!glfwInititialized) {
	if (!glfwInit())
	    return NULL; // TODO add log system
	glfwInititialized = true;
	std::cout << "glfw initialized !" << std::endl;
    }
    tinyGL::Core* e = NULL;

    std::thread* t = new std::thread(_exec, &e, t);
    while (!e) {std::cout << "wait for engine*" << std::endl; } // wierd lock to wait for the construction of the engine...

    GLFWwindow* w = glfwCreateWindow(640, 480, "TODO", NULL, NULL);
    std::cout << "window inititialized" << std::endl;
    if (!w) {
	std::cout << "failed to create window" << std::endl; // TODO add log system
	glfwTerminate();
	return NULL; 
    }
    e->_window = w;
    return e;
}

void tinyGL::Core::_exec(tinyGL::Core** e_, std::thread* t_) {
    std::cout << "run" << std::endl;
    *e_ = new Core();
    (*e_)->_scope = t_;
    std::cout << "yay" << std::endl;
    (*e_)->_coreLoop();
}
