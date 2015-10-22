#include "renderTexture.hh"

GRand::RenderTexture::RenderTexture(unsigned int width_, unsigned int height_) {
    _loaded = true;
    std::cout << "res: " << width_ << " " << height_ << std::endl;
    //texture
    glActiveTexture(GL_TEXTURE0);
    GPUGen();

    // RenderBuffer
    glGenRenderbuffers(1, &_depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width_, height_);

    // frameBuffer
    glGenFramebuffers(1, &_framebufferID);
    glBindFramebuffer(GL_FRAMEBUFFER, _framebufferID);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _textureId, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthBuffer);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (GLsizei)width_, (GLsizei)height_, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _textureId, 0);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
	std::cout << "\033[31mglCheckFramebufferStatus: error " << status << "\033[0m" << std::endl;
    }

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

void GRand::RenderTexture::load() {
}
