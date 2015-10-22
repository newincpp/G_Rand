#include <glm/gtc/matrix_transform.hpp>
#include "camera.hh"

GRand::Camera::Camera(Core* e_) : _core(e_), _center(0.0f), _target(0.0f) {
    static const float tanHalfFovy = tanf(0.858f / 2.0f); // focale length from blender
    // replace tanf with some inline assembly to replace the boring gnu stuff (FPTAN) or directly write the result ?
    static const float zFar = 1000.0f;
    static const float zNear = 1.0f;
    static const float zRange = zFar - zNear;

    _uproj.get()[0][0] = 1.0f / ((16.0f/9.0f) * tanHalfFovy);
    _uproj.get()[0][1] = 0.0f;
    _uproj.get()[0][2] = 0.0f;
    _uproj.get()[0][3] = 0.0f;

    _uproj.get()[1][0] = 0.0f;
    _uproj.get()[1][1] = 1.0f / (tanHalfFovy);
    _uproj.get()[1][2] = 0.0f;
    _uproj.get()[1][3] = 0.0f;

    _uproj.get()[2][0] = 0.0f;
    _uproj.get()[2][1] = 0.0f;
    _uproj.get()[2][2] = (-zFar - zNear) / zRange;
    _uproj.get()[2][3] = 2.0f * zFar * zNear / zRange;

    _uproj.get()[3][0] = 0.0f;
    _uproj.get()[3][1] = 0.0f;
    _uproj.get()[3][2] = 1.0f;
    _uproj.get()[3][3] = 0.0f;
    _utrans.get() = MatType(1.0f);
    _utrans.__manual_Location_setting__(4);
    _uproj.__manual_Location_setting__(5);
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
    _uproj.upload();
    _utrans.upload();
}
