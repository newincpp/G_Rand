#include "GPUBuffer.hh"

#define VERTEX_LOCATION_ 0
#define NORMAL_LOCATION_ 1
#define UV_LOCATION_ 2

GRand::GPUBuffer::GPUBuffer() : _vbo(0), _ebo(0), _hasNormals(false), _hasTexture(false) {
}

GRand::GPUBuffer::GPUBuffer(const GPUBuffer& o_) : _vbo(o_._vbo), _ebo(o_._ebo), _hasNormals(o_._hasNormals), _hasTexture(o_._hasTexture) {
    if (_vbo == 0) {
	_vertexArray = o_._vertexArray;
    }
    if (_ebo == 0) {
	_elementArray = o_._elementArray;
    }
}

void GRand::GPUBuffer::operator=(const GPUBuffer& o_) {
    _vbo = o_._vbo;
    _ebo = o_._ebo;
    _hasNormals = o_._hasNormals;
    _hasTexture = o_._hasTexture;
    if (_vbo) {
	return;
    }
    _vertexArray = o_._vertexArray;
    _elementArray = o_._elementArray;
}

void GRand::GPUBuffer::regenVboEbo() {
    if (_vbo) {
	glDeleteBuffers(1, &_vbo);
	glDeleteBuffers(1, &_ebo);
    }
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, _vertexArray.size() * sizeof(decltype(_vertexArray)::value_type), &(_vertexArray[0]), GL_STATIC_DRAW);

    glGenBuffers(1, &_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _elementArray.size() * sizeof(decltype(_vertexArray)::value_type), &(_elementArray[0]), GL_STATIC_DRAW);





    int numberFloatsPerVertex = 3 + (3 * _hasNormals) + (2 * _hasTexture); // there are always the 3 coord of the vertex
    glVertexAttribPointer(VERTEX_LOCATION_, 3, GL_FLOAT, GL_FALSE, numberFloatsPerVertex * sizeof(decltype(_vertexArray)::value_type), (void*)0); // vertex
    if (_hasNormals) {
	glVertexAttribPointer(NORMAL_LOCATION_, 3, GL_FLOAT, GL_FALSE, numberFloatsPerVertex * sizeof(decltype(_vertexArray)::value_type), (void*)(3 * sizeof(decltype(_vertexArray)::value_type))); //normal
    }
    if (_hasTexture) {
	glVertexAttribPointer(UV_LOCATION_, 2, GL_FLOAT, GL_FALSE, numberFloatsPerVertex * sizeof(decltype(_vertexArray)::value_type), (void*)(6 * sizeof(decltype(_vertexArray)::value_type))); //uv
    }
}

void GRand::GPUBuffer::setBuffer() {
    if (_vbo) {
	glDeleteBuffers(1, &_vbo);
    }
    regenVboEbo();
}

GRand::GPUBuffer::~GPUBuffer() {
    GPUFree();
}

void GRand::GPUBuffer::GPUFree() {
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_ebo);
}

void GRand::GPUBuffer::CPUFree() {
    _vertexArray.clear();
    _elementArray.clear();
}

void GRand::GPUBuffer::draw(GLenum drawStyle_) const noexcept {
    glEnableVertexAttribArray(VERTEX_LOCATION_); // enable vertex shader parameter value
    glEnableVertexAttribArray(NORMAL_LOCATION_); // enable normal shader parameter value
    glEnableVertexAttribArray(UV_LOCATION_);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    // draw the polygon with the shader on the OpenGL draw buffer
    glDrawElements(drawStyle_, _elementArray.size(), GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(VERTEX_LOCATION_);
    glDisableVertexAttribArray(NORMAL_LOCATION_);
    glDisableVertexAttribArray(UV_LOCATION_);
}
