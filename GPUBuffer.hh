#ifndef GPUBUFFER_H_
# define GPUBUFFER_H_
#include <GL/glew.h>
#include <assimp/Importer.hpp>
#include <string>
#include <vector>

namespace GRand {
    class GPUBuffer {
	private:
	    GLuint _vbo;
	    const aiScene* _scene;
	    std::vector<GLfloat> _vertexArray;
	    void getAllFaces(const struct aiNode*);
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
