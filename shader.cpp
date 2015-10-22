#include <GL/glew.h>
#include <GL/gl.h>
#include "shader.hh"

GRand::Shader::Shader(GLenum type, const std::string& filename) : _shaderId(0), _compiled(false) {
    _shaderId = glCreateShader(type);
    getStringFromFile(filename);
    const char* source = _source.c_str();
    glShaderSource(_shaderId, 1, &source, NULL);
    std::cout << "compiling: " << filename << std::endl;
    compile();
}

GRand::Shader::Shader(const Shader& s_) : _shaderId(s_._shaderId), _compiled(s_._compiled), _source(s_._source) {
}

void GRand::Shader::compile() {
    glCompileShader(_shaderId);
    _compiled = _checkCompile();
}

GRand::Shader::~Shader() {
}
