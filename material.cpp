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
		    if (compileStatus) {
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
}

const char* const GRand::Material::_StexStringArray_[8] = {
    "tex[0]",
    "tex[1]",
    "tex[2]",
    "tex[3]",
    "tex[4]",
    "tex[5]",
    "tex[7]",
};

GRand::Material::Material(Core* c_) : _shaderProgram(0), _core(c_) {
}

void GRand::Material::_addShader(GLenum type_, const std::string& filename_) noexcept {
    _shaders.emplace_back(type_, filename_);
}

void GRand::Material::addShader(GLenum type_, const std::string& filename_) noexcept {
    _core->queueIntruction(std::bind(&::GRand::Material::_addShader, this, type_, filename_));
}

void GRand::Material::link() noexcept {
    _core->queueIntruction(std::bind(&::GRand::Material::_link, this));
}

void GRand::Material::_link() noexcept {
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
    glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &linkStatus);
    if (linkStatus != GL_TRUE) {
	GLint InfoLogLength;
	glGetProgramiv(_shaderProgram, GL_INFO_LOG_LENGTH, &InfoLogLength);
	char ErrorMessage[InfoLogLength];
	glGetProgramInfoLog(_shaderProgram, InfoLogLength, NULL, ErrorMessage);
	std::cout << "\033[0;31mfailed to link error log: " << std::endl << ErrorMessage << std::endl << "-------------------\033[0m" << std::endl;
    } else {
	std::cout << "\033[0;32msuccessfully linked\033[0m" << std::endl;
    }

    _uTextureAmount.__manual_Location_setting__(8);
    _samplerArrayLocation = glGetUniformLocation(_shaderProgram, "tex");
}

void GRand::Material::use() const noexcept {
    unsigned int i = 0;
    glEnable(GL_TEXTURE_2D);

    for (decltype(_textures)::value_type t : _textures) {
	t->bind(GL_TEXTURE0 + i);
        glUniform1i(glGetUniformLocation(_shaderProgram, _StexStringArray_[i]), i);
    }
    _uTextureAmount.upload(); 
    glUseProgram(_shaderProgram);
}

decltype(GRand::Material::_textures)::const_iterator GRand::Material::addTexture(Texture* t_) {
    GLint maxTex;
    glGetIntegerv(GL_MAX_TEXTURE_UNITS, &maxTex);
    if ((int)_textures.size() > maxTex) {
	std::cout << "\e[33myou are exeeding the maximum amout of textures:" << maxTex << "\e[0m" << std::endl;
    }
    if (!t_->isLoaded()) {
	t_->load();
    }
    _textures.push_back(t_);
    _uTextureAmount.get() = _textures.size();
    return _textures.end()--;
}

void GRand::Material::excludeTexture(decltype(_textures)::iterator iterator_) {
    _textures.erase(iterator_);
}

decltype(GRand::Material::_textures)& GRand::Material::getTextureList() {
    return _textures;
}

GRand::Material::~Material() {
    for (Shader& s: _shaders) {
	glDeleteShader(s.getId());
    }
}
