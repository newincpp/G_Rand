#ifndef MATERIAL_H_
# define MATERIAL_H_

#include <vector>

namespace GRand {
    class Shader;
    class Material {
	private:
	    GLuint _shaderProgram;
	    std::vector<Shader> _shaders;
	public:
	    explicit Material();
	    void addShader(GLenum, const std::string&) noexcept;
	    void use();
	    ~Material();
    };
}

#endif /* !MATERIAL_H_ */
