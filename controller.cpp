#include "controller.hh"

GRand::Controller::Controller(matType& l_) : _transform(l_) {
    _transform = matType::Identity();
    _utrans.get() = _transform;
    _utrans.__manual_Location_setting__(2);
}

void GRand::Controller::translate(const Eigen::Vector3f& f_) {
//    _transform.rightCols(1) += Eigen::Vector4f(f_.x(), f_.y(), f_.z(), 1);
    Eigen::Affine3f t;
    t.setIdentity();
    t.translate(f_);
    _transform = t.matrix() * _transform;
}

void GRand::Controller::rotate(float angle_, const Eigen::Vector3f& f_) {
    Eigen::Affine3f t;
    t.setIdentity();
    t.rotate(Eigen::AngleAxisf(angle_, f_));
    _transform = t.matrix() * _transform;
}

void GRand::Controller::scale(const Eigen::Vector3f& f_) {
    Eigen::Affine3f t;
    t.setIdentity();
    t.scale(f_);
    _transform = t.matrix() * _transform;
}

void GRand::Controller::setUniform(const decltype(_utrans)& _newUniform) {
    _utrans.copyLocation(_newUniform);
}

void GRand::Controller::refresh() {
    _utrans.get() = _transform;
    _utrans.upload();
}
