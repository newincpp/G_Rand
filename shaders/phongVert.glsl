#version 440

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vUVCoord;
layout(location = 3) uniform mat4 model;
layout(location = 4) uniform mat4 camera;
layout(location = 5) uniform mat4 proj;
out vec3 fNormal;
out vec3 fVertex;
out vec2 fUVCoord;
out vec3 eye;

void main() {
    //mat4 proj = mat4(1);
    //float tanHalfFovy = tan(0.858 /2); // focale length from blender
    //float zFar = 1000;
    //float zNear = 1;
    //float zRange = zFar - zNear;

    //proj[0][0] = 1.0 / ((16/9) * tanHalfFovy);
    //proj[0][1] = 0.0;
    //proj[0][2] = 0.0;
    //proj[0][3] = 0.0;

    //proj[1][0] = 0.0;
    //proj[1][1] = 1.0 / (tanHalfFovy);
    //proj[1][2] = 0.0;
    //proj[1][3] = 0.0;

    //proj[2][0] = 0.0;
    //proj[2][1] = 0.0;
    //proj[2][2] = (-zFar - zNear) / zRange;
    //proj[2][3] = 2.0 * zFar * zNear / zRange;

    //proj[3][0] = 0.0;
    //proj[3][1] = 0.0;
    //proj[3][2] = 1.0;
    //proj[3][3] = 0.0;

    vec4 p = vec4(vPos, 1.0);
    fNormal = vNormal;
    fVertex = (model * p).xyz;
    fUVCoord = vUVCoord;
    eye.x = -camera[0][3];
    eye.y = -camera[1][3];
    eye.z = -camera[2][3];
    gl_Position = proj * camera * model * p;
}
