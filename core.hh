#ifndef STARTUPENGINE_H_
# define STARTUPENGINE_H_

#include <string>
#include <functional>
#include <vector>
#include <queue>
#include <thread>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace GRand {
    class Core {
	private:
	    explicit Core();
	    static void _exec(Core**, std::thread*);
	    void _coreLoop();

	    void _interal_WaitForWindow_();
	    void _interal_render_();
	    GLFWwindow* _window;
	    std::thread* _scope;
	    std::function<void()> _state;
	    std::queue<std::function<void(void)>> _instructionQueue;
	    std::vector<std::function<void(void)>> _instructionList;
	    bool _validState;

	    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	public:
	    struct Config {
		unsigned int winWidth;
		unsigned int winHeight;
		std::string winName;
		int refreshRate;
		bool fullscreen;
		static void autoConf(Config&);
	    };

	    virtual ~Core();
	    static Core* start(const Config&);
	    void queueIntruction(const std::function<void()>& instruction_) { _instructionQueue.push(instruction_); }
	    void addPersistantInstruction(const std::function<void()>& instruction_) { _instructionList.push_back(instruction_); }
	    bool getStateValidity();
    };
}

#endif /* !STARTUPENGINE_H_ */
