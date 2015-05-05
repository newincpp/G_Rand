#include "controller.hh"

GRand::Controller::Controller(Eigen::Matrix3f& l_) : _transform(l_) {
}

void GRand::Controller::translate(const Eigen::Vector3f& f_) {
    _transform.col(3) += f_;
}

void GRand::Controller::rotate(float angle_, const Eigen::Vector3f& f_) {
    _transform = Eigen::AngleAxisf(angle_, f_) * _transform;
}

void GRand::Controller::scale(const Eigen::Vector3f& f_) {
    _transform = Eigen::Scaling(f_) * _transform;
}

void GRand::Controller::setUniform(const decltype(_utrans)& _newUniform) {
    _utrans.copyLocation(_newUniform);
}

void GRand::Controller::refresh() {
    _utrans.get() = _transform;
    _utrans.upload();
}
