#include "mesh.hh"

GRand::Mesh::Mesh(Core* e_, Material* m_) : _core(e_), _material(m_), _transform(Eigen::Matrix3f::Identity()) {
    _core->addPersistantInstruction(std::bind(&Mesh::_render, this));
}

void GRand::Mesh::set(const GPUBuffer& b_) noexcept {
    _gb = b_;
}

GRand::Controller* GRand::Mesh::genController() {
    _remote = std::make_shared<Controller>(_transform);
    return _remote.get();
}

GRand::Controller* GRand::Mesh::getController() {
    return _remote.get();
}

GRand::Mesh::~Mesh() {
}

void GRand::Mesh::_render() const noexcept{
    _material->use();
}
