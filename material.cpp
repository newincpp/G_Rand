#include <iostream>
#include <fstream>
#include <string>
#include <GL/glew.h>
#include <GL/gl.h>
#include "material.hh"

namespace GRand {
	class Shader {
	    private:
		GLuint _shaderId;
		inline const char* getStringFromFile(const std::string& filename) const noexcept {
		    std::ifstream t(filename);
		    const std::string _t((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
		    return _t.c_str();
		}
		inline void _checkCompile()const noexcept {
		     GLint InfoLogLength;
		     glGetShaderiv(_shaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
		     char ErrorMessage[InfoLogLength];
		     glGetShaderInfoLog(_shaderId, InfoLogLength, NULL, ErrorMessage);
		     std::cout << "error log: " << std::endl << ErrorMessage << std::endl << "-------------------" << std::endl;
		}
	    public:
		explicit Shader(GLenum, const std::string&);
		void compile()noexcept;
		GLuint getShaderId()const noexcept;
		~Shader();
	};
}

GRand::Shader::Shader(GLenum type, const std::string& filename) : _shaderId(0) {
    _shaderId = glCreateShader(type);
    const char* _ = getStringFromFile(filename);
    glShaderSource(_shaderId, 1, &_, NULL);
}

void GRand::Shader::compile() noexcept {
    std::cout << "compiling shaders..." << std::endl;
    glCompileShader(_shaderId);
    std::cout << "shader compiled" << std::endl;
    _checkCompile();
}



GRand::Shader::~Shader() {
}

GRand::Material::Material() : _shaderProgram(0) {
}

void GRand::Material::addShader(GLenum type, const std::string& filename) noexcept {
_shaders.push_back(Shader(type, filename));
}

void GRand::Material::use() {
    glUseProgram(_shaderProgram);
}

GRand::Material::~Material() {
}
