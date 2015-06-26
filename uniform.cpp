#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
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
void Uniform<unsigned int>::upload() const {
    glUniform1ui(_location, _value);
}
template <>
void Uniform<glm::vec2>::upload() const {
    glUniform2f(_location, _value[0], _value[1]);
}
template <>
void Uniform<glm::vec3>::upload() const {
    glUniform3f(_location, _value[0], _value[1], _value[2]);
}
template <>
void Uniform<glm::vec4>::upload() const {
    glUniform4f(_location, _value[0], _value[1], _value[2], _value[3]);
}

//MATRIX

template <>
void Uniform<glm::mat2>::upload() const {
    glUniformMatrix2fv(_location, 1, GL_FALSE, glm::value_ptr(_value));
}
template <>
void Uniform<glm::mat3>::upload() const {
    glUniformMatrix3fv(_location, 1, GL_FALSE, glm::value_ptr(_value));
}
template <>
void Uniform<glm::mat4>::upload() const {
    glUniformMatrix4fv(_location, 1, GL_FALSE, glm::value_ptr(_value));
}
template <>
void Uniform<glm::mat2x3>::upload() const {
    glUniformMatrix2x3fv(_location, 1, GL_FALSE, glm::value_ptr(_value));
}
template <>
void Uniform<glm::mat3x2>::upload() const {
    glUniformMatrix3x2fv(_location, 1, GL_FALSE, glm::value_ptr(_value));
}
template <>
void Uniform<glm::mat2x4>::upload() const {
    glUniformMatrix2x4fv(_location, 1, GL_FALSE, glm::value_ptr(_value));
}
template <>
void Uniform<glm::mat4x2>::upload() const {
    glUniformMatrix4x2fv(_location, 1, GL_FALSE, glm::value_ptr(_value));
}
template <>
void Uniform<glm::mat3x4>::upload() const {
    glUniformMatrix3x4fv(_location, 1, GL_FALSE, glm::value_ptr(_value));
}
template <>
void Uniform<glm::mat4x3>::upload() const {
    glUniformMatrix4x3fv(_location, 1, GL_FALSE, glm::value_ptr(_value));
}
