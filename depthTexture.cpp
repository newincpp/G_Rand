#include "depthTexture.hh"

template <>
GRand::DepthTexture<true>::DepthTexture(_Int, _Int) {
    glGenFramebuffers(1, &_fbId.value);
    glBindFramebuffer(GL_FRAMEBUFFER_EXT, _fbId.value);

    GLint viewPortInfo[4];

    glGetIntegerv( GL_VIEWPORT, viewPortInfo);

    glGenTextures(1, &_texId);
    glBindTexture(GL_TEXTURE_2D, _texId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, viewPortInfo[0], viewPortInfo[1], 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, _texId, 0);

    glFramebufferTexture2D(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, _texId, 0);
    glBindFramebuffer(GL_FRAMEBUFFER_EXT, 0);
}

template <>
GRand::DepthTexture<false>::DepthTexture(_Int width_, _Int height_) {
    glGenTextures(1, &_texId);
    glBindTexture(GL_TEXTURE_2D, _texId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width_.value, height_.value, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, _texId, 0);
}
