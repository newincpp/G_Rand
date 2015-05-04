#version 330

layout(location = 0) in vec3 uPos;

void main() {
    gl_Position = vec4(uPos, 1.0);
}
