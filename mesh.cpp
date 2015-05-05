#include <iostream>
#include "mesh.hh"

GRand::Mesh::Mesh(Core* e_, Material* m_) : _core(e_), _material(m_), _transform(Eigen::Matrix3f::Identity()) {
    _core->addPersistantInstruction(std::bind(&Mesh::_render, this));
}

void GRand::Mesh::set(const GPUBuffer&) noexcept {
    _core->queueIntruction(std::bind(&Mesh::_uploadBuffer, this));
}

GRand::Controller* GRand::Mesh::genController() {
    _remote = std::make_shared<Controller>(_transform);
    return _remote.get();
}

GRand::Controller* GRand::Mesh::getController() {
    return _remote.get();
}

void GRand::Mesh::setExistantController(std::shared_ptr<GRand::Controller> c_) {
    _remote = c_;
}

GRand::Mesh::~Mesh() {
}

void GRand::Mesh::_render() const noexcept{
    _material->use();
    _gb.draw(GL_TRIANGLES);
}

void GRand::Mesh::_uploadBuffer() noexcept {
    //_gb.generateVBOAndVertexArray(); 

    //tmp body for testing
    std::vector<GLfloat> vertices = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f,  .0f, 0.0f,
    };

    _gb.loadFile("/home/sicarde/monkey.dae");
    _gb.generateVBOAndVertexArray();
    //_gb.setBuffer(vertices);
}
