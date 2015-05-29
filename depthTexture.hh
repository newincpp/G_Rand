#ifndef DEPTHFRAMEBUFFER_H_
# define DEPTHFRAMEBUFFER_H_

#include "core.hh"
#include "templateHelper.hh"

namespace GRand {
    template <bool FrameBufferMode = true>
    class DepthTexture {
	private:
	    typedef DeclareIf<GLuint, !FrameBufferMode> _Int;
	    DeclareIf<GLuint, FrameBufferMode> _fbId;
	    GLuint _texId;
	public:
	    explicit DepthTexture(_Int, _Int);
    };
}

#endif /* !DEPTHFRAMEBUFFER_H_ */
