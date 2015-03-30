#include <iostream>
#include "engine.hh"

tinyGL::Engine::Engine() : _window(NULL), _state(std::bind(&tinyGL::Engine::_interal_WaitForWindow_, this)), _validState(true) {
}

tinyGL::Engine::~Engine() {
    glfwTerminate();
    _scope->join();
}

void tinyGL::Engine::_interal_WaitForWindow_() {
    if (_window) {
	glfwMakeContextCurrent(_window);
	_state = std::bind(&tinyGL::Engine::_interal_render_, this);
    }
}

void tinyGL::Engine::_interal_render_() {
	glClear(GL_COLOR_BUFFER_BIT);
	if (_instructionQueue.size()) {
	    _instructionQueue.front()();
	    _instructionQueue.pop();
	}
	glfwSwapBuffers(_window);
	glfwPollEvents();
	_validState = !glfwWindowShouldClose(_window);
}

void tinyGL::Engine::_coreLoop() {
    while (_validState)
	_state();
}

tinyGL::Engine* tinyGL::Engine::start() {
    static bool glfwInititialized;
    if (!glfwInititialized) {
	if (!glfwInit())
	    return NULL; // TODO add log system
	glfwInititialized = true;
	std::cout << "glfw initialized !" << std::endl;
    }
    tinyGL::Engine* e = NULL;

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

void tinyGL::Engine::_exec(tinyGL::Engine** e_, std::thread* t_) {
    std::cout << "run" << std::endl;
    *e_ = new Engine();
    (*e_)->_scope = t_;
    std::cout << "yay" << std::endl;
    (*e_)->_coreLoop();
}
