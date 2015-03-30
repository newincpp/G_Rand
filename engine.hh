#ifndef STARTUPENGINE_H_
# define STARTUPENGINE_H_

#include <string>
#include <functional>
#include <queue>
#include <thread>
#include <GLFW/glfw3.h>

namespace tinyGL {
    class Engine {
	public:
	    virtual ~Engine();
	    static Engine* start();
	    void queueIntruction(const std::function<void()>& instruction_) { _instructionQueue.push(instruction_); }
	private:
	    explicit Engine();
	    static void _exec(Engine**, std::thread*);
	    void _coreLoop();

	    void _interal_WaitForWindow_();
	    void _interal_render_();
	    GLFWwindow* _window;
	    std::thread* _scope;
	    std::function<void()> _state;
	    std::queue<std::function<void(void)>> _instructionQueue;
	    bool _validState;
    };
}

#endif /* !STARTUPENGINE_H_ */
