#ifndef GPUBUFFER_H_
# define GPUBUFFER_H_
#include <string>
#include <vector>
#include <uniform.hh>
#include <GL/glew.h>
#include <eigen3/Eigen/Dense>
#include <assimp/Importer.hpp>

namespace GRand {
    class GPUBuffer {
	private:
	    GLuint _vbo;
	    const aiScene* _scene;
	    std::vector<GLfloat> _vertexArray;
	    void getAllFaces(const struct aiScene *sc, const struct aiNode*);
	public:
	    explicit GPUBuffer();
	    GPUBuffer(const GPUBuffer&);
	    ~GPUBuffer();
	    void operator=(const GPUBuffer&);
	    void setBuffer(const std::vector<GLfloat>&);
	    bool loadFile(std::string const &name);
	    void generateVBOAndVertexArray();
	    void draw(GLenum drawStyle_)const noexcept;
    };
}

#endif /* !GPUBUFFER_H_ */
