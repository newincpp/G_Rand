#include "EigenUtility.hh"
#include "camera.hh"

GRand::Camera::Camera(Core* e_) : _core(e_), _center(Eigen::Vector3f::Zero()), _target(Eigen::Vector3f::Zero()) {
    _utrans.get() = matType::Identity();
    _utrans.__manual_Location_setting__(4);
    _core->addPersistantInstruction(std::bind(&Camera::_refresh, this));
}

void GRand::Camera::translate(const Eigen::Vector3f& f_) {
    _center += f_;
    _utrans.get() = ::lookAt<float>(_center, _target, Eigen::Vector3f::UnitY());
}

void GRand::Camera::setPos(const Eigen::Vector3f& f_) {
    _center = f_;
    _utrans.get() = ::lookAt<float>(_center, _target, Eigen::Vector3f::UnitY());
}

void GRand::Camera::lookAt(const Eigen::Vector3f& f_) {
    _target = f_;
    _utrans.get() = ::lookAt<float>(_center, _target, Eigen::Vector3f::UnitY());
}

void GRand::Camera::_refresh() {
    _utrans.upload();
}
