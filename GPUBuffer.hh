#ifndef GPUBUFFER_H_
# define GPUBUFFER_H_
#include <GL/glew.h>
#include <vector>

namespace GRand {
    class GPUBuffer {
	private:
	    GLuint _vbo;
	public:
	    explicit GPUBuffer();
	    GPUBuffer(const GPUBuffer&);
	    ~GPUBuffer();
	    void operator=(const GPUBuffer&);
	    void setBuffer(const std::vector<GLfloat>&);
    };
}

#endif /* !GPUBUFFER_H_ */