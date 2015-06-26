#include <glm/gtc/matrix_transform.hpp>
#include "camera.hh"

GRand::Camera::Camera(Core* e_) : _core(e_), _center(0.0f), _target(0.0f) {
    _utrans.get() = MatType(1.0f);
    _utrans.__manual_Location_setting__(4);
    _core->addPersistantInstruction(std::bind(&Camera::_refresh, this));
}

void GRand::Camera::translate(const Camera::VectorType& f_) {
    _center += f_;
    _utrans.get() = glm::lookAt(_center, _target, Camera::VectorType(0.0f, 1.0f, 0.0f));
}

void GRand::Camera::setPos(const Camera::VectorType& f_) {
    _center = f_;
    _utrans.get() = glm::lookAt(_center, _target, Camera::VectorType(0.0f, 1.0f, 0.0f));
}

void GRand::Camera::lookAt(const Camera::VectorType& f_) {
    _target = f_;
    _utrans.get() = glm::lookAt(_center, _target, Camera::VectorType(0.0f, 1.0f, 0.0f));
}

void GRand::Camera::_refresh() {
    _utrans.upload();
}
