#ifndef STARTUPENGINE_H_
# define STARTUPENGINE_H_

#include <string>
#include <functional>
#include <vector>
#include <queue>
#include <map>
#include <thread>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "renderTexture.hh"

namespace GRand {
    class Material;
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
	    std::map<int, std::function<void(void)>> _inputMap;
	    bool _validState;
	    RenderTexture* _rtt;
	    GLuint _renderVbo;
	    GLuint _vboFboID;
	    GLint _postProcessProgram;

	    void _rmFunc(unsigned long);
	    void _genPPvbo();
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
	    void setMaterialPostProcess(GRand::Material&);
    };
}

#define PUSH_CORE_INST(e, exp) e->queueIntruction([](){ exp; });
#define PUSH_CORE_INSTA(e, arg, exp) e->queueIntruction([&arg](){ exp; });

#endif /* !STARTUPENGINE_H_ */
