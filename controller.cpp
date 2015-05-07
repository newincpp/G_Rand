#include "controller.hh"

GRand::Controller::Controller(matType& l_) : _transform(l_) {
    _transform = matType::Identity();
    _utrans.get() = _transform;
    _utrans.__manual_Location_setting__(2);
}

void GRand::Controller::translate(const Eigen::Vector3f& f_) {
//    _transform.rightCols(1) += Eigen::Vector4f(f_.x(), f_.y(), f_.z(), 1);
    Eigen::Affine3f t;
    t.translate(f_);
    _transform = t.matrix();
}

void GRand::Controller::rotate(float angle_, const Eigen::Vector3f& f_) {
    Eigen::Affine3f t;
    t.rotate(Eigen::AngleAxisf(angle_, f_));
    _transform = t.matrix();
    //_transform = Eigen::AngleAxisf(angle_, f_).toRotationMatrix().z() * _transform;
}

void GRand::Controller::scale(const Eigen::Vector3f& f_) {
    Eigen::Transform<float,3,Eigen::Affine> t;
    t.scale(f_);
    _transform = t.matrix();
}

void GRand::Controller::setUniform(const decltype(_utrans)& _newUniform) {
    _utrans.copyLocation(_newUniform);
}

void GRand::Controller::refresh() {
    _utrans.get() = _transform;
    _utrans.upload();
}
