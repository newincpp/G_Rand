#include "texture.hh"

GRand::Texture::Texture(const std::string& fname_) : _loaded(false), _textureId(0), _filename(fname_) {
    ilGenImages(1, &_imgId);
}

GRand::Texture::~Texture() {
    ilDeleteImage(_imgId);
}

void GRand::Texture::load() noexcept {
    if (!_textureId) {
	 glDeleteTextures(1, &_textureId);
	 _textureId = 0;
    }
    ilBindImage(_imgId);
    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);	
    if (!ilLoadImage(_filename.c_str())) {
	ilDeleteImages(1, &_imgId); 
	return;
    }
    glGenTextures(1, &_textureId);
    glBindTexture(GL_TEXTURE_2D, _textureId);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //glGenerateMipmap(GL_TEXTURE_2D);

    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, GL_RGBA, GL_UNSIGNED_BYTE, ilGetData());
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);
    _loaded = true;
}
