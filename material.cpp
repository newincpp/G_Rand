#include <GL/glew.h>
#include <GL/gl.h>
#include "material.hh"

const char* const GRand::Material::_StexStringArray_[16] = {
    "tex[0]",
    "tex[1]",
    "tex[2]",
    "tex[3]",
    "tex[4]",
    "tex[5]",
    "tex[7]",
    "tex[8]",
    "tex[9]",
    "tex[10]",
    "tex[11]",
    "tex[12]",
    "tex[13]",
    "tex[14]",
    "tex[15]",
};

GRand::Material::Material(Core* c_) : _shaderProgram(0), _core(c_) {
    _uTextureAmount.get() = 0;
}

void GRand::Material::_addShader(GLenum type_, const std::string& filename_) {
    _shaders.emplace_back(type_, filename_);
}

void GRand::Material::addShader(GLenum type_, const std::string& filename_) {
    _core->queueIntruction(std::bind(&::GRand::Material::_addShader, this, type_, filename_));
}

void GRand::Material::link() {
    _core->queueIntruction(std::bind(&::GRand::Material::_link, this));
}

void GRand::Material::_link() {
    if (_shaderProgram) {
	glDeleteProgram(_shaderProgram);
    }
    _shaderProgram = glCreateProgram();
    for (Shader& s : _shaders) {
	if (!s.getCompileStatus()) {
	    std::cout << "\033[33m warning: not compiled shader found\033[0m" << std::endl;
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
	std::cout << "\033[32msuccessfully linked\033[0m" << std::endl;
    }

    _uTextureAmount.__manual_Location_setting__(8);
    //_samplerArrayLocation = glGetUniformLocation(_shaderProgram, "tex");
}

void GRand::Material::use() const {
    if (!_shaderProgram) {
	std::cout << "invalid shader program id" << _shaderProgram << std::endl;
	return;
    }
    glUseProgram(_shaderProgram);
    _uTextureAmount.upload(); 
    if (_textures.size() != _uTextureAmount.get()) {
	std::cout << "program id: " << _shaderProgram << std::endl;
	std::cout << "\033[31;1m_texture.size() = " << _textures.size() << " != uniform TextureAmount = " << _uTextureAmount.get() << "\e[0m" << std::endl;
	return;
    }
    unsigned int i = 0;
    for (decltype(_textures)::value_type t : _textures) {
	t->bind(GL_TEXTURE0 + i);
        glUniform1i(glGetUniformLocation(_shaderProgram, _StexStringArray_[i]), i);
	++i;
    }
}

decltype(GRand::Material::_textures)::const_iterator GRand::Material::addTexture(Texture* t_) {
    GLint maxTex;
    glGetIntegerv(GL_MAX_TEXTURE_UNITS, &maxTex);
    if ((int)_textures.size() > maxTex) {
	std::cout << "\e[33myou are exeeding the maximum amout of textures:" << maxTex << "\e[0m" << std::endl;
    }
    if (!t_->isLoaded()) {
	_core->queueIntruction([t_](){ t_->load(); });
    }
    _textures.push_back(t_);
    _uTextureAmount.get() = (unsigned int)_textures.size();
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
