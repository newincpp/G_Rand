#ifndef MATERIAL_H_
# define MATERIAL_H_

#include <vector>
#include <uniform.hh>

namespace GRand {
    class Shader;
    class Material {
	private:
	    GLuint _shaderProgram;
	    std::vector<Shader> _shaders;
	public:
	    explicit Material();
	    void addShader(GLenum, const std::string&) noexcept;
	    void link()noexcept;
	    void use()const noexcept;
	    void compileAll()noexcept;
	    template <typename T>
	    Uniform<T> getUniform(const std::string&);
	    ~Material();
    };
}

template <typename T> Uniform<T> GRand::Material::getUniform(const std::string& name) {
    return Uniform<T>(T(), _shaderProgram, name);
}

#endif /* !MATERIAL_H_ */
