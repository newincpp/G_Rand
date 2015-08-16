#include "renderTexture.hh"

GRand::RenderTexture::RenderTexture(unsigned int width_, unsigned int height_) {
    glGenFramebuffers(1, &_framebufferID);
    glBindFramebuffer(GL_FRAMEBUFFER, _framebufferID);
    glGenRenderbuffers(1, &_depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width_, height_);
    GPUGen();

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, GRand::Texture::_textureId, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthBuffer);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GRand::RenderTexture::bindFramebuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, _framebufferID);
}

GRand::RenderTexture::~RenderTexture() {
    GPUFree();
    glDeleteFramebuffers(1, &_framebufferID);
    glDeleteRenderbuffers(1, &_depthBuffer);
}

void GRand::RenderTexture::load()noexcept{
}
