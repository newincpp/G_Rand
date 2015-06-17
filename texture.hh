#ifndef TEXTURE_H_
# define TEXTURE_H_

#include "uniform.hh"
#include <GL/glew.h>

namespace GRand {
    class Texture {
	private:
	    GLuint _textureId;
	public:
	    explicit Texture();
	    virtual ~Texture();
	    virtual void load()noexcept;
	    void locate()noexcept;
	    inline void use(unsigned int index_) const noexcept {
		glActiveTexture(GL_TEXTURE0 + index_);
		glBindTexture(GL_TEXTURE_2D, _textureId);
	    }
    };
}

#endif /* !TEXTURE_H_ */
