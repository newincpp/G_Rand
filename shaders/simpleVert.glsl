#version 330

layout(location = 0) in vec3 vPos;
uniform mat3 model;

void main() {
    vec3 p = model * vPos;
    gl_Position = vec4(p, 1.0);
}
