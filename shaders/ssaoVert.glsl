#version 330

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vNormal;
uniform mat3 model;

void main() {
    vec3 p = model * vPos;
    gl_Position = vec4(p, 1.0);
}