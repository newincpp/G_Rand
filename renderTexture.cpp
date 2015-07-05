#include "renderTexture.hh"

GRand::RenderTexture::RenderTexture(unsigned int width, unsigned int height) {
    glGenFramebuffers(1, &_framebufferID);
    glBindFramebuffer(GL_FRAMEBUFFER, _framebufferID);
    glGenRenderbuffers(1, &_depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthBuffer);
    GPUGen();
}

void GRand::RenderTexture::bindFramebuffer() {
    //glBindFramebuffer(GL_FRAMEBUFFER, _framebufferID);
    glBindFramebuffer(GL_FRAMEBUFFER, _framebufferID);
}

GRand::RenderTexture::~RenderTexture() {
    glDeleteFramebuffers(1, &_framebufferID);
}
