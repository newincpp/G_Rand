#ifndef GPUBUFFER_H_
# define GPUBUFFER_H_
#include <string>
#include <vector>
#include <uniform.hh>
#include <GL/glew.h>
#include <assimp/Importer.hpp>

namespace GRand {
    class GPUBuffer {
	private:
	    GLsizei _elementBufferSize; // for performance reason
	    GLuint _vbo;
	    GLuint _ebo;
	    bool _hasNormals; // should be a bitfield
	    bool _hasTexture;
	public:
	    explicit GPUBuffer();
	    GPUBuffer(const GPUBuffer&);
	    ~GPUBuffer();
	    GPUBuffer& operator=(const GPUBuffer&);
	    //inline decltype(_vertexArray)& getVertexArray() { return _vertexArray; }
	    //inline decltype(_elementArray)& getElementArray() { return _elementArray; }
	    inline void setHasNormals(bool&& b_) { _hasNormals = b_; }
	    inline void setHasTexture(bool&& b_) { _hasTexture = b_; }
	    void setBuffer();
	    void regenVboEbo(const std::vector<GLfloat>&, const std::vector<GLuint>&);
	    void GPUFree();
	    void CPUFree();
	    void draw(GLenum drawStyle_)const;
    };
}

#endif /* !GPUBUFFER_H_ */
