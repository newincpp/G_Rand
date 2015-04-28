#ifndef GPUBUFFER_H_
# define GPUBUFFER_H_
#include <GL/glew.h>
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
	    void loadFile();
	    void generateVBOAndVertexArray();
    };
}

#endif /* !GPUBUFFER_H_ */
