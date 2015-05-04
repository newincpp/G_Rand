#version 330
in vec2 Texcoord;
layout(location = 1) out vec4 outColor;
uniform sampler2D textureSampleId;
uniform vec4 filterColor;
uniform mat3 frameMatrix;
void main() {
       vec2 txc = (vec3(Texcoord, 1) * frameMatrix).xy;
       outColor = texture(textureSampleId, txc) + filterColor;
}
