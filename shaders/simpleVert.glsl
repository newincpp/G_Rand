#version 330

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vNormal;
layout(location = 2) uniform mat3 model;
uniform mat3 model;

void main() {
    vec3 p = model * vPos;
    gl_Position = vec4(p, 1.0);
}
