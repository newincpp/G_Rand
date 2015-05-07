#include <eigen3/Eigen/Dense>
#include "uniform.hh"

//VECTORS
template <>
void Uniform<float>::upload() const {
	glUniform1f(_location, _value);
}
template <>
void Uniform<int>::upload() const {
	glUniform1i(_location, _value);
}
template <>
void Uniform<Eigen::Vector2f>::upload() const {
	glUniform2f(_location, _value[0], _value[1]);
}
template <>
void Uniform<Eigen::Vector3f>::upload() const {
	glUniform3f(_location, _value[0], _value[1], _value[2]);
}
template <>
void Uniform<Eigen::Vector4f>::upload() const {
	glUniform4f(_location, _value[0], _value[1], _value[2], _value[3]);
}

//MATRIX

template <>
void Uniform<Eigen::Matrix2f>::upload() const {
	glUniformMatrix2fv(_location, 1, GL_FALSE, _value.data());
}
template <>
void Uniform<Eigen::Matrix3f>::upload() const {
	glUniformMatrix3fv(_location, 1, GL_FALSE, _value.data());
}
template <>
void Uniform<Eigen::Matrix4f>::upload() const {
	glUniformMatrix4fv(_location, 1, GL_FALSE, _value.data());
}
template <>
void Uniform<Eigen::Matrix<float, 2, 3> >::upload() const {
	glUniformMatrix2x3fv(_location, 1, GL_FALSE, _value.data());
}
template <>
void Uniform<Eigen::Matrix<float, 3, 2> >::upload() const {
	glUniformMatrix3x2fv(_location, 1, GL_FALSE, _value.data());
}
template <>
void Uniform<Eigen::Matrix<float, 2, 4> >::upload() const {
	glUniformMatrix2x4fv(_location, 1, GL_FALSE, _value.data());
}
template <>
void Uniform<Eigen::Matrix<float, 4, 2> >::upload() const {
	glUniformMatrix4x2fv(_location, 1, GL_FALSE, _value.data());
}
template <>
void Uniform<Eigen::Matrix<float, 3, 4> >::upload() const {
	glUniformMatrix3x4fv(_location, 1, GL_FALSE, _value.data());
}
template <>
void Uniform<Eigen::Matrix<float, 4, 3> >::upload() const {
	glUniformMatrix4x3fv(_location, 1, GL_FALSE, _value.data());
}
