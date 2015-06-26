#include "controller.hh"
#include <glm/gtx/transform.hpp>

GRand::Controller::Controller() {
    _utrans.get() = MatType(1.0f);
    _utrans.__manual_Location_setting__(0);
}

void GRand::Controller::translate(const VectorType& f_) {
    _utrans.get() *= glm::translate(f_);
}

void GRand::Controller::rotate(float angle_, const VectorType& f_) {
    _utrans.get() *= glm::rotate(angle_, f_);
}

void GRand::Controller::scale(const VectorType& f_) {
    _utrans.get() *= glm::scale(f_);
}

void GRand::Controller::setUniform(const decltype(_utrans)& _newUniform) {
    _utrans.copyLocation(_newUniform);
}

void GRand::Controller::refresh() {
    std::cout << "?" << std::endl;
    _utrans.upload();
}
