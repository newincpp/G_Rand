#pragma once

#include <string>
#include <functional>
#include <vector>
#include <queue>
#include <map>
#include <thread>
#include <mutex>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "renderTexture.hh"

namespace GRand {
    class ppMaterial;
    class Core {
	private:
	    explicit Core();
	    static void _exec(Core**, std::mutex*);
	    void _coreLoop();

	    void _interal_WaitForWindow_();
	    void _interal_render_();
	    GLFWwindow* _window;
	    std::thread* _scope;
	    std::function<void()> _state;
	    std::queue<std::function<void(void)>> _instructionQueue;
	    std::vector<std::function<void(void)>> _instructionList;
	    std::map<int, std::function<void(void)>> _inputMap;
	    bool _validState;
	    RenderTexture* _rtt;
	    ppMaterial* _postProcessMaterial;
	    GLuint _renderVbo;
	    float _rendertime; // in nanosecond

	    void _rmFunc(unsigned long);
	    void _genPPvbo();
	    void _postProcessInit();
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
	    void queueIntruction(const std::function<void()>& instruction_);
	    unsigned long addPersistantInstruction(const std::function<void()>& instruction_);
	    void deletePersistantInstruction(unsigned long i_);
	    void addInputCallback(int, const std::function<void(void)>&);
	    bool getStateValidity();
	    void noPostProcess(bool=false);
	    inline float getRenderTime() const { return _rendertime; };
    };
}

#define PUSH_CORE_INST(e, exp) e->queueIntruction([](){ exp; });
#define PUSH_CORE_INSTA(e, arg, exp) e->queueIntruction([&arg](){ exp; });
#define TO_SECOND(x) (x / 1000000000)
