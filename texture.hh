#ifndef TEXTURE_H_
# define TEXTURE_H_

#include <string>
#include <GL/glew.h>
#include "uniform.hh"
#include "IL/il.h"

namespace GRand {
    class Texture {
	private:
	    static const char* const _glErrorToString[7];
	    ILuint _imgId;
	    void _load();
	    std::string _filename;
	protected:
	    bool _loaded;
	    GLuint _textureId;
	public:
	    explicit Texture(const std::string& = "");
	    virtual ~Texture();
	    virtual void load();
	    void locate(GLuint);
	    void GPUFree();
	    void GPUGen();
	    inline bool isLoaded() const { return _loaded; }
	    inline void setFilename(const std::string& f_) { _filename = f_; }
	    inline void bind(GLenum textureUnit_) const {
		glActiveTexture(textureUnit_);
		glBindTexture(GL_TEXTURE_2D, _textureId);
	    }
    };
}

#endif /* !TEXTURE_H_ */
