#ifndef RENDERTEXTURE_H_
# define RENDERTEXTURE_H_

#include "texture.hh"
namespace GRand {
    class RenderTexture : Texture {
	private:
	    GLuint _framebufferID;
	public:
	    explicit RenderTexture();
	    
	    ~RenderTexture();
    };
}

#endif /* !RENDERTEXTURE_H_ */
