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
		    if (compileStatus == GL_TRUE) {
			std::cout << "\033[0;32msuccesfully compiled\033[0m" << std::endl;
			return true;
		    }
		    GLint InfoLogLength;
		    glGetShaderiv(_shaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
		    char ErrorMessage[InfoLogLength];
		    glGetShaderInfoLog(_shaderId, InfoLogLength, NULL, ErrorMessage);
		    std::cout << "\033[1;31mfailed to compile shader!" << std::endl <<
			"your shader:" << std::endl << 
			_source << std::endl <<
			"error log:" << std::endl << ErrorMessage << std::endl << "-------------------\033[0m" << std::endl;
		    return false;
		}
	    public:
		explicit Shader(GLenum, const std::string&);
		Shader(Shader&&);
		void compile()noexcept;
		inline GLuint getId()const noexcept { return _shaderId; }
		inline bool getCompileStatus()const noexcept { return _compiled; }
		~Shader();
	};
}

GRand::Shader::Shader(GLenum type, const std::string& filename) : _shaderId(0), _compiled(false) {
    _shaderId = glCreateShader(type);
    getStringFromFile(filename);
    const char* source = _source.c_str();
    glShaderSource(_shaderId, 1, &source, NULL);
    std::cout << "compiling: " << filename << std::endl;
    compile();
}

GRand::Shader::Shader(Shader&& s_) : _shaderId(s_._shaderId), _compiled(s_._compiled), _source(s_._source) {
}

void GRand::Shader::compile() noexcept {
    glCompileShader(_shaderId);
    _compiled = _checkCompile();
}

GRand::Shader::~Shader() {
    //std::cout << "deleting shader " << _shaderId << std::endl;
}

GRand::Material::Material() : _shaderProgram(0) {
}

void GRand::Material::addShader(GLenum type, const std::string& filename) noexcept {
    _shaders.emplace_back(type, filename);
}

void GRand::Material::link() noexcept {
    if (!_shaderProgram) {
	glDeleteProgram(_shaderProgram);
    }
    _shaderProgram = glCreateProgram();
    for (Shader& s : _shaders) {
	if (!s.getCompileStatus()) {
	    std::cout << "\033[1;33m warning: not compiled shader found\033[0m" << std::endl;
	}
	glAttachShader(_shaderProgram, s.getId());
    }
    glLinkProgram(_shaderProgram);


    GLint linkStatus;
    glGetShaderiv(_shaderProgram,  GL_LINK_STATUS, &linkStatus);
    if (linkStatus == GL_FALSE) {
	GLint InfoLogLength;
	glGetProgramiv(_shaderProgram, GL_INFO_LOG_LENGTH, &InfoLogLength);
	char ErrorMessage[InfoLogLength];
	glGetProgramInfoLog(_shaderProgram, InfoLogLength, NULL, ErrorMessage);
	std::cout << "\033[0;31mfailed to link error log: " << std::endl << ErrorMessage << std::endl << "-------------------\033[0m" << std::endl;
    }
    std::cout << "\033[0;32msuccessfully linked\033[0m" << std::endl;
}

void GRand::Material::use() const noexcept {
    glUseProgram(_shaderProgram);
}

GRand::Material::~Material() {
    for (Shader& s: _shaders) {
	glDeleteShader(s.getId());
    }
}
