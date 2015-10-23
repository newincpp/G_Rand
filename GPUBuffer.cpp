#include "GPUBuffer.hh"

#define VERTEX_LOCATION_ 0
#define NORMAL_LOCATION_ 1
#define UV_LOCATION_ 2

GRand::GPUBuffer::GPUBuffer() : _elementBufferSize(0), _vbo(0), _ebo(0), _hasNormals(false), _hasTexture(false) {
}

GRand::GPUBuffer::GPUBuffer(const GPUBuffer& o_) : _elementBufferSize(0), _vbo(o_._vbo), _ebo(o_._ebo), _hasNormals(o_._hasNormals), _hasTexture(o_._hasTexture) {
}

GRand::GPUBuffer& GRand::GPUBuffer::operator=(const GPUBuffer& o_) {
    _vbo = o_._vbo;
    _ebo = o_._ebo;
    _hasNormals = o_._hasNormals;
    _hasTexture = o_._hasTexture;
    return *this;
}

void GRand::GPUBuffer::regenVboEbo(const std::vector<GLfloat>& vertexArray_, const std::vector<GLuint>& elementArray_) {
    typedef std::remove_reference<decltype(vertexArray_)>::type::value_type vArray_T;
    typedef std::remove_reference<decltype(elementArray_)>::type::value_type eArray_T;
    if (_vbo) {
	glDeleteBuffers(1, &_vbo);
	glDeleteBuffers(1, &_ebo);
    }
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, vertexArray_.size() * sizeof(vArray_T), &(vertexArray_[0]), GL_STATIC_DRAW);

    glGenBuffers(1, &_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementArray_.size() * sizeof(eArray_T), &(elementArray_[0]), GL_STATIC_DRAW);

    unsigned long numberFloatsPerVertex = 3 + (3 * _hasNormals) + (2 * _hasTexture); // there are always the 3 coord of the vertex
    glVertexAttribPointer(VERTEX_LOCATION_, 3, GL_FLOAT, GL_FALSE, numberFloatsPerVertex * sizeof(vArray_T), (void*)0); // vertex
    if (_hasNormals) {
	glVertexAttribPointer(NORMAL_LOCATION_, 3, GL_FLOAT, GL_FALSE, numberFloatsPerVertex * sizeof(vArray_T), (void*)(3 * sizeof(vArray_T))); //normal
    }
    if (_hasTexture) {
	glVertexAttribPointer(UV_LOCATION_, 2, GL_FLOAT, GL_FALSE, numberFloatsPerVertex * sizeof(vArray_T), (void*)(6 * sizeof(vArray_T))); //uv
    }
    _elementBufferSize = (GLsizei)elementArray_.size();
}

void GRand::GPUBuffer::setBuffer() {
    if (_vbo) {
	glDeleteBuffers(1, &_vbo);
    }
    //regenVboEbo();
}

GRand::GPUBuffer::~GPUBuffer() {
    GPUFree();
}

void GRand::GPUBuffer::GPUFree() {
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_ebo);
}

void GRand::GPUBuffer::CPUFree() {
    _elementBufferSize = 0;
}

void GRand::GPUBuffer::draw(GLenum drawStyle_) const {
    glEnableVertexAttribArray(VERTEX_LOCATION_); // enable vertex shader parameter value
    glEnableVertexAttribArray(NORMAL_LOCATION_); // enable normal shader parameter value
    glEnableVertexAttribArray(UV_LOCATION_);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    // draw the polygon with the shader on the OpenGL draw buffer
    //glDrawElements(drawStyle_, (GLsizei)_elementArray.size(), GL_UNSIGNED_INT, 0);
    glDrawElements(drawStyle_, _elementBufferSize, GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(VERTEX_LOCATION_);
    glDisableVertexAttribArray(NORMAL_LOCATION_);
    glDisableVertexAttribArray(UV_LOCATION_);
}
