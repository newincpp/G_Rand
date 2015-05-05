#version 330

in vec3 fNormal;
out vec4 outColor;

void main() {
    vec3 lightPos(1.5,1,0);
    outColor = vec4(0,0.3,0, 1.0);
}
