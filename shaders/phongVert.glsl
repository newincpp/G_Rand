#version 440

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vNormal;
layout(location = 2) uniform mat4 model;
layout(location = 3) uniform mat4 view;
out vec3 fNormal;
out vec3 eye;

void main() {
    mat4 proj = mat4(1.0);
    float tanHalfFovy = tan(0.785 / 2);
    float zFar = 100000;
    float zNear = 0.5;

    proj[0][0] = 1.0 / ((16.0/9.0) * tanHalfFovy);
    proj[1][1] = 1.0 / (tanHalfFovy);
    proj[2][2] = - (zFar + zNear) / (zFar - zNear);
    proj[3][2] = - 1.0;
    proj[2][3] = - (2.0 * zFar * zNear) / (zFar - zNear);

    vec4 p = vec4(vPos, 1.0) ;
    fNormal = vNormal;
    eye.x = -view[0][3];
    eye.y = -view[1][3];
    eye.z = -view[2][3];
    gl_Position = proj * view * model * p;
}
