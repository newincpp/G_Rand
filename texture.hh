#ifndef TEXTURE_H_
# define TEXTURE_H_

#include <string>
#include <GL/glew.h>
#include "uniform.hh"
#include "IL/il.h"

namespace GRand {
    class Texture {
	private:
	    bool _loaded;
	    ILuint _imgId;
	    GLuint _textureId;
	    std::string _filename;
	public:
	    explicit Texture(const std::string& = "");
	    virtual ~Texture();
	    virtual void load()noexcept;
	    void locate(GLuint)noexcept;
	    inline bool isLoaded() const noexcept { return _loaded; }
	    inline void setFilename(const std::string& f_) { _filename = f_; }
	    inline void bind() const noexcept {
		glBindTexture(GL_TEXTURE_2D, _textureId);
	    }
    };
}

#endif /* !TEXTURE_H_ */
