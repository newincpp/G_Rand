#ifndef RENDERTEXTURE_H_
# define RENDERTEXTURE_H_

#include "texture.hh"

namespace GRand {
    class RenderTexture : public Texture {
	private:
	    GLuint _framebufferID;
	    GLuint _depthBuffer;
	public:
	    explicit RenderTexture(unsigned int, unsigned int);
	    void bindFramebuffer();
	    virtual void load()noexcept;
	    
	    ~RenderTexture();
    };
}

#endif /* !RENDERTEXTURE_H_ */

/*
     glGenTextures(1, &_fbo_texture);
     glBindTexture(GL_TEXTURE_2D, _fbo_texture);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
     glBindTexture(GL_TEXTURE_2D, 0);
 
     // Depth buffer 
     glGenRenderbuffers(1, &_rbo_depth);
     glBindRenderbuffer(GL_RENDERBUFFER, _rbo_depth);
     glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, _screenSize[0] , _screenSize[1]);
     glBindRenderbuffer(GL_RENDERBUFFER, 0);
 
     // Framebuffer to link everything together 
     glGenFramebuffers(1, &_fbo);
     glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
     glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _fbo_texture, 0);
     glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _rbo_depth);
     GLenum status;
     if ((status = glCheckFramebufferStatus(GL_FRAMEBUFFER)) != GL_FRAMEBUFFER_COMPLETE) {
                  std::cout << "glCheckFramebufferStatus: error " << status << std::endl;
      }
      glBindFramebuffer(GL_FRAMEBUFFER, 0);
      GLfloat fbo_vertices[] = {
                      -1, -1,
                      1, -1,
                      -1,  1,
                      1,  1,
          };
     glGenBuffers(1, &_vbo_fbo_vertices);
     glBindBuffer(GL_ARRAY_BUFFER, _vbo_fbo_vertices);
     glBufferData(GL_ARRAY_BUFFER, sizeof(fbo_vertices), fbo_vertices, GL_STATIC_DRAW);
     glBindBuffer(GL_ARRAY_BUFFER, 0);
 
         const char* vertsrc =
                 "#version 330\n"
                 "in vec2 v_coord;"
                 "uniform sampler2D fbo_texture;"
                 "out vec2 f_texcoord;"
                 "void main(void) {"                                                                                                                                                           
                 "       vec2 finalSize = v_coord;"
                 "       gl_Position = vec4(finalSize, 0.0, 1.0);"
                 "       f_texcoord = (v_coord+ 1.0) / 2.0;"
         "}";
     const char* fragsrc =
         "#version 330\n"
         "uniform sampler2D fbo_texture;"
         "uniform float fade;"
         "in vec2 f_texcoord;"
         "out vec4 outColor;"
         "void main(void) {"
         "       outColor = texture(fbo_texture, f_texcoord) * fade;"
         "}";
 
 
     // Create and compile the vertex shader
     GLuint fbVs = glCreateShader(GL_VERTEX_SHADER);
     glShaderSource(fbVs, 1, &vertsrc, NULL);
     glCompileShader(fbVs);
     _checkCompileShader(fbVs);
 
     // Create and compile the fragment shader
     GLuint fbFs = glCreateShader(GL_FRAGMENT_SHADER);
     glShaderSource(fbFs, 1, &fragsrc, NULL);
     glCompileShader(fbFs);
     _checkCompileShader(fbFs);
 
     _program_postproc = glCreateProgram();
     glAttachShader(_program_postproc, fbVs);
     glAttachShader(_program_postproc, fbFs);
     glLinkProgram(_program_postproc);
 
     _attribute_v_coord_postproc = glGetAttribLocation(_program_postproc, "v_coord");
 
     _ufade.relocate(_program_postproc, "fade");
     _ufade = 0;
 
     _uniform_fbo_texture = glGetUniformLocation(_program_postproc, "fbo_texture");
*/
