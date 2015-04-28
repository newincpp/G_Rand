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
		    GLint compileStatus;
		    glGetShaderiv(_shaderId, GL_COMPILE_STATUS, &compileStatus);
		    if (compileStatus == GL_TRUE) {
			return
		    }
		     GLint InfoLogLength;
		     glGetShaderiv(_shaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
		     char ErrorMessage[InfoLogLength];
		     glGetShaderInfoLog(_shaderId, InfoLogLength, NULL, ErrorMessage);
		     std::cout << "error log: " << std::endl << ErrorMessage << std::endl << "-------------------" << std::endl;
		}
	    public:
		explicit Shader(GLenum, const std::string&);
		void compile()noexcept;
		inline GLuint getId()const noexcept { return _shaderId; }
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
    glDeleteShader(_shaderId);
}

GRand::Material::Material() : _shaderProgram(0) {
}

void GRand::Material::addShader(GLenum type, const std::string& filename) noexcept {
    _shaders.push_back(Shader(type, filename));
}

void GRand::Material::link() noexcept {
    std::cout << "linking shaders" << std::endl;
    if (!_shaderProgram) {
	glDeleteProgram(_shaderProgram);
    }
    _shaderProgram = glCreateProgram();
    for (Shader& s : _shaders) {
	glAttachShader(_shaderProgram, s.getId());
    }
    glLinkProgram(_shaderProgram);


    GLint compileStatus;
    glGetShaderiv(_shaderId,  GL_LINK_STATUS, &compileStatus);
    if (compileStatus == GL_TRUE) {
	std::cout << "shader successfully compiled" << std::endl;
	return;
    }
    GLint InfoLogLength;
    glGetProgramiv(_shaderProgram, GL_INFO_LOG_LENGTH, &InfoLogLength);
    char ErrorMessage[InfoLogLength];
    glGetProgramInfoLog(_shaderProgram, InfoLogLength, NULL, ErrorMessage);
    std::cout << "error log: " << std::endl << ErrorMessage << std::endl << "-------------------" << std::endl;
}

void GRand::Material::use() noexcept {
    glUseProgram(_shaderProgram);
}

GRand::Material::~Material() {
}
