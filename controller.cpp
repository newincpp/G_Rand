#include "controller.hh"

GRand::Controller::Controller() {
    _transform.setIdentity();
    _utrans.get() = _transform.matrix();
    _utrans.__manual_Location_setting__(0);
}

void GRand::Controller::translate(const Eigen::Vector3f& f_) {
    //_transform.rightCols(1) += Eigen::Vector4f(f_.x(), f_.y(), f_.z(), 1);
    _transform.translate(f_);
}

void GRand::Controller::rotate(float angle_, const Eigen::Vector3f& f_) {
    _transform.rotate(Eigen::AngleAxisf(angle_, f_));
}

void GRand::Controller::scale(const Eigen::Vector3f& f_) {
    _transform.scale(f_);
}

void GRand::Controller::setUniform(const decltype(_utrans)& _newUniform) {
    _utrans.copyLocation(_newUniform);
}

void GRand::Controller::refresh() {
    _utrans.get() = _transform.matrix();
    _utrans.upload();
}
