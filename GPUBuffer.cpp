#include "GPUBuffer.hh"

GRand::GPUBuffer::GPUBuffer() {
    glGenBuffers(1, &_vbo);
}

void GRand::GPUBuffer::setBuffer(const std::vector<GLfloat>& b_) {
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, b_.size(), &b_[0], GL_STATIC_DRAW);
}

GRand::GPUBuffer::~GPUBuffer() {
    glDeleteBuffers(1, &_vbo);
}
