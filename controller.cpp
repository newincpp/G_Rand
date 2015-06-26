#include "controller.hh"
#include <glm/gtc/type_ptr.hpp>
#include "glm/gtx/transform.hpp"

GRand::Controller::Controller() {
    _utrans.get() = MatType(1.0f);
    _utrans.__manual_Location_setting__(3);
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
    _utrans.upload();
}
