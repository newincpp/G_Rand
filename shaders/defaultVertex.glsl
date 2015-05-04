#version 330
layout(location = 0) in vec3 vPos;
in vec2 texcoord;
out vec2 Texcoord;
uniform mat3 displacement;
uniform vec2 cameraPosition;
uniform int screenSpace;
uniform mat3 topMatrix;

void main() {
   Texcoord = texcoord;
   vec3 pos = vPos * displacement * topMatrix;
   if (screenSpace == 1) {
       gl_Position = vec4(pos, 1.0);
   } else {
       gl_Position = vec4(pos - vec3(cameraPosition, 0), 1.0);
   }
}
