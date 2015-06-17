#include "renderTexture.hh"

GRand::RenderTexture::RenderTexture() {
    glGenFramebuffers(1, &_framebufferID);
    glBindFramebuffer(GL_FRAMEBUFFER, _framebufferID);
}

GRand::RenderTexture::~RenderTexture() {
}
