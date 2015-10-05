#include "postProcMaterial.hh"

GRand::ppMaterial::ppMaterial(Core* e_, RenderTexture* rt_) : Material(e_) {
    addShader(GL_VERTEX_SHADER, "./shaders/2DVert.glsl");
    addShader(GL_FRAGMENT_SHADER, "./shaders/simpleFrag.glsl");
    link();
    addTexture(rt_);
}

GRand::ppMaterial::~ppMaterial() {
}
