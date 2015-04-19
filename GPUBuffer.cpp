#include "GPUBuffer.hh"

GRand::GPUBuffer::GPUBuffer() : _vbo(0) {
}

GRand::GPUBuffer::GPUBuffer(const GPUBuffer& o_) : _vbo(o_._vbo) {
}

void GRand::GPUBuffer::operator=(const GPUBuffer& o_) {
    _vbo = o_._vbo;
}

void GRand::GPUBuffer::setBuffer(const std::vector<GLfloat>& b_) {
    if (_vbo) {
	glDeleteBuffers(1, &_vbo);
    }
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, b_.size(), &b_[0], GL_STATIC_DRAW);
}

GRand::GPUBuffer::~GPUBuffer() {
}
