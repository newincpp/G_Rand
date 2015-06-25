#ifndef MATERIAL_H_
# define MATERIAL_H_

#include <vector>
#include <string>
#include <array>
#include <uniform.hh>
#include "core.hh"
#include "texture.hh"

namespace GRand {
    class Shader;
    class Material {
	private:
	    static const char* const _StexStringArray_[16];
	    GLuint _shaderProgram;
	    GLuint _samplerArrayLocation;
	    Core* _core;
	    Uniform<unsigned int> _uTextureAmount;
	    std::vector<Shader> _shaders;
	    std::vector<const Texture*> _textures;
	    void _link()noexcept;
	    void _addShader(GLenum, const std::string&) noexcept;
	public:
	    explicit Material(Core*);
	    void addShader(GLenum, const std::string&) noexcept;
	    void link()noexcept;
	    void use()const noexcept;
	    void compileAll()noexcept;
	    decltype(_textures)::const_iterator addTexture(Texture*);
	    void excludeTexture(decltype(_textures)::iterator);
	    template <typename T> Uniform<T> getUniform(const std::string&);
	    inline decltype(_textures)& getTextureList();
	    ~Material();
    };
}

template <typename T> Uniform<T> GRand::Material::getUniform(const std::string& name) {
    return Uniform<T>(T(), _shaderProgram, name);
}

#endif /* !MATERIAL_H_ */
