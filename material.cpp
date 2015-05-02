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
			std::cout << "\033[1;32mcompilation done with success\033[0m" << std::endl;
			return;
		    }
		    GLint InfoLogLength;
		    glGetShaderiv(_shaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
		    char ErrorMessage[InfoLogLength];
		    glGetShaderInfoLog(_shaderId, InfoLogLength, NULL, ErrorMessage);
		    std::cout << "\033[1;31mfailed to compile shader, error log: " << std::endl << ErrorMessage << std::endl << "-------------------\033[0m" << std::endl;
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
    const char* source = getStringFromFile(filename);
    std::cout << source << std::endl;
    glShaderSource(_shaderId, 1, &source, NULL);
    std::cout << "new id: " << _shaderId << " " << filename << std::endl;
}

void GRand::Shader::compile() noexcept {
    std::cout << "compiling shader..." << std::endl;
    glCompileShader(_shaderId);
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
	s.compile();
	glAttachShader(_shaderProgram, s.getId());
    }
    glLinkProgram(_shaderProgram);


    GLint compileStatus;
    glGetShaderiv(_shaderProgram,  GL_LINK_STATUS, &compileStatus);
    if (compileStatus == GL_TRUE) {
	std::cout << "shader successfully compiled" << std::endl;
	return;
    }
    GLint InfoLogLength;
    glGetProgramiv(_shaderProgram, GL_INFO_LOG_LENGTH, &InfoLogLength);
    char ErrorMessage[InfoLogLength];
    glGetProgramInfoLog(_shaderProgram, InfoLogLength, NULL, ErrorMessage);
    std::cout << "\033[0;31mfailed to link error log: " << std::endl << ErrorMessage << std::endl << "-------------------\033[0m" << std::endl;
}

void GRand::Material::use() const noexcept {
    glUseProgram(_shaderProgram);
}

GRand::Material::~Material() {
}
