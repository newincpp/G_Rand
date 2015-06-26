#include "mesh.hh"

GRand::Mesh::Mesh(Core* e_, Material* m_) : _core(e_), _material(m_), _remote(NULL) {
    if (!e_) {
	std::cout << "\e[31;1mgiving null as a pointer to Core will result to a segmentation fault\e0m" << std::endl;
    } if (!m_) {
	std::cout << "\e[31;1mgiving null as a pointer to Material will result to a segmentation fault\e0m" << std::endl;
    }
    std::cout << "add mesh" << std::endl;
}

void GRand::Mesh::set(const GPUBuffer& b_) noexcept {
    _gb = b_;
    _core->queueIntruction(std::bind(&Mesh::_uploadBuffer, this));
    _core->addPersistantInstruction(std::bind(&Mesh::_render, this));
}

void GRand::Mesh::fromFile(const std::string& fname_) {
    _gb.loadFile(fname_);
    _core->queueIntruction(std::bind(&Mesh::_uploadBuffer, this));
    _core->addPersistantInstruction(std::bind(&Mesh::_render, this));
}

GRand::Controller* GRand::Mesh::genController() {
    _remote = std::make_shared<Controller>();
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
    //_remote->refresh();
    _gb.draw(GL_TRIANGLES);
}

void GRand::Mesh::_uploadBuffer() noexcept {
    _gb.regenVboEbo();
}
