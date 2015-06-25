#include "renderTexture.hh"

GRand::RenderTexture::RenderTexture() : Texture(NULL) {
    glGenFramebuffers(1, &_framebufferID);
    glBindFramebuffer(GL_FRAMEBUFFER, _framebufferID);
}

GRand::RenderTexture::~RenderTexture() {
}
