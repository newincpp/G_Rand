#version 440

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vNormal;
layout(location = 2) uniform mat4 model;
layout(location = 3) uniform mat4 view;
layout(location = 4) uniform mat4 projection;
out vec3 fNormal;

void main() {
    mat4 proj;
    float tanHalfFovy = tan((3.1415926 / 2) / 2);
    float zFar = 100000;
    float zNear = 0.1;

    proj[0][0] = 1.0 / ((16.0/9.0) * tanHalfFovy);
    proj[1][1] = 1.0 / (tanHalfFovy);
    proj[2][2] = - (zFar + zNear) / (zFar - zNear);
    proj[3][2] = - 1.0;
    proj[2][3] = - (2.0 * zFar * zNear) / (zFar - zNear);


    vec3 lightPos = vec3(1.5,1,0);
    vec4 p = vec4(vPos, 1.0);
    p = proj * view * model * p;
    fNormal = vNormal;
    gl_Position = p;
}
