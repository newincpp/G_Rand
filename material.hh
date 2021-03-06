#pragma once

#include <vector>
#include <string>
#include <array>
#include <uniform.hh>
#include "core.hh"
#include "texture.hh"
#include "shader.hh"

namespace GRand {
    class Material {
	private:
	    static const char* const _StexStringArray_[16];
	    GLuint _shaderProgram;
	    //GLint _samplerArrayLocation;
	    Core* _core;
	    Uniform<unsigned int> _uTextureAmount;
	    std::vector<Shader> _shaders;
	    std::vector<const Texture*> _textures;
	    void _link();
	    void _addShader(GLenum, const std::string&);
	public:
	    explicit Material(Core*);
	    ~Material();
	    void addShader(GLenum, const std::string&);
	    void link();
	    void use()const;
	    void compileAll();
	    decltype(_textures)::const_iterator addTexture(Texture*);
	    void excludeTexture(decltype(_textures)::iterator);
	    template <typename T> Uniform<T> getUniform(const std::string&);
	    inline decltype(_textures)& getTextureList();
	    inline GLuint getShaderProgram()const {
		return _shaderProgram;
	    }

    };
}

template <typename T> Uniform<T> GRand::Material::getUniform(const std::string& name) {
    return Uniform<T>(T(), _shaderProgram, name);
}
