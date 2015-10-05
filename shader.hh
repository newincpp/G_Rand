#ifndef SHADER_H_
# define SHADER_H_

#include <iostream>
#include <fstream>
#include <string>

namespace GRand {
	class Shader {
	    private:
		GLuint _shaderId;
		bool _compiled;
		std::string _source;
		inline void getStringFromFile(const std::string& filename) noexcept {
		    std::ifstream t(filename);
		    const std::string s((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
		    _source = s;
		}
		inline bool _checkCompile()const noexcept {
		    GLint compileStatus;
		    glGetShaderiv(_shaderId, GL_COMPILE_STATUS, &compileStatus);
		    if (compileStatus) {
			std::cout << "\033[32msuccesfully compiled\033[0m" << std::endl;
			return true;
		    }
		    GLint InfoLogLength;
		    glGetShaderiv(_shaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
		    char ErrorMessage[InfoLogLength];
		    glGetShaderInfoLog(_shaderId, InfoLogLength, NULL, ErrorMessage);
		    std::cout << "\033[31mfailed to compile shader!\033[0m" << std::endl <<
			"your shader:" << std::endl << 
			_source << std::endl <<
			"error log:" << std::endl << ErrorMessage << std::endl << "-------------------\033[0m" << std::endl;
		    return false;
		}
	    public:
		explicit Shader(GLenum, const std::string&);
		Shader(const Shader&);
		void compile()noexcept;
		inline GLuint getId()const noexcept { return _shaderId; }
		inline bool getCompileStatus()const noexcept { return _compiled; }
		~Shader();
	};
}

#endif /* !SHADER_H_ */
