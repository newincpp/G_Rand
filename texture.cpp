#include "texture.hh"

GRand::Texture::Texture() {
}

GRand::Texture::~Texture() {
}

void GRand::Texture::load() noexcept {
    if (!_textureId) {
	 glDeleteTextures(1, &_textureId);
    }
    glGenTextures(1, &_textureId);
    glBindTexture(GL_TEXTURE_2D, _textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);


    /* need to be remplaced by loading function */
    float pixels[] = {
	0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f
    };
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);
}

void GRand::Texture::locate() noexcept {
}
