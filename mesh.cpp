#include "mesh.hh"

GRand::Mesh::Mesh(Core* e_, Material* m_) : _core(e_), _material(m_), _transform(Eigen::Matrix3f::Identity()) {
    _core->addPersistantInstruction(std::bind(&Mesh::_render, this));
    //addPersistantInstruction(const std::function<void()>& instruction_);
}

void GRand::Mesh::set(const GPUBuffer& b_) {
    _gb = b_;
}

GRand::Mesh::~Mesh() {
}

void GRand::Mesh::_render() const noexcept{
    _material->use();
}
