#version 330

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vNormal;
out vec3 fNormal;
uniform mat3 model;

void main() {
    vec3 lightPos(1.5,1,0);
    vec3 p = model * vPos;
    fNormal = vNormal;
    gl_Position = vec4(p, 1.0);
}
