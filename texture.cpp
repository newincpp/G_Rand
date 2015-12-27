#include "texture.hh"

const char* const GRand::Texture::_glErrorToString[9] = {
    "GL_INVALID_ENUM", // 1280
    "GL_INVALID_VALUE", // 1281
    "GL_INVALID_OPERATION", // 1282
    "GL_STACK_OVERFLOW", // 1283
    "GL_STACK_UNDERFLOW", // 1284
    "GL_OUT_OF_MEMORY", // 1285
    "GL_INVALID_FRAMEBUFFER_OPERATION", // 1286
    "GL_CONTEXT_LOST", // 1287
    "GL_TABLE_TOO_LARGE" // 1288
};

GRand::Texture::Texture(const std::string& fname_) : _imgId(0), _filename(fname_), _loaded(false), _textureId(0) {
}

GRand::Texture::~Texture() {
    if (_imgId) {
	ilDeleteImage(_imgId);
    }
}

void GRand::Texture::load() {
    if (!_textureId) {
	 glDeleteTextures(1, &_textureId);
	 _textureId = 0;
    }
    GPUGen();
    glGenerateMipmap(GL_TEXTURE_2D);

    if (_filename.size() == 0) {
	std::cout << "\e[33;1mno texture file name, using the default one\e[0m" << std::endl;
	float pixels[] = {
	    .7f, .7f, .7f,   .7f, .0f, .0f,
	    .7f, .0f, .0f, .7f, .7f, .7f
	};
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);
	return;
    }
    std::cout << "loading file: " << _filename << std::endl;
    ilGenImages(1, &_imgId);
    ilBindImage(_imgId);
    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);	
    if (!ilLoadImage(_filename.c_str())) {
	std::cout << "\e[31;1mfailed to load: " << _filename << "\e[0m" << std::endl;
	return;
    }
    ilConvertImage(IL_RGBA, IL_FLOAT);

    glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_FLOAT, ilGetData());
    std::cout << ilGetInteger(IL_IMAGE_WIDTH) << " " <<  ilGetInteger(IL_IMAGE_HEIGHT) << " " <<  GL_RGBA << " " << ilGetInteger(IL_IMAGE_BPP) << " " << GL_RGBA << " " << ilGetInteger(IL_IMAGE_FORMAT) << std::endl;
    GLenum errCode;
    while ((errCode = glGetError()) != GL_NO_ERROR) {
	std::cout << _glErrorToString[errCode - GL_INVALID_ENUM] << ":" << errCode << std::endl;
    }
    _loaded = true;
}

void GRand::Texture::GPUGen() {
    glGenTextures(1, &_textureId);
    glBindTexture(GL_TEXTURE_2D, _textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void GRand::Texture::GPUFree() {
    if (_textureId) {
	 glDeleteTextures(1, &_textureId);
	 _textureId = 0;
    }
}
