#ifndef MESH_H_
# define MESH_H_

#include "GPUBuffer.hh"
#include "core.hh"
#include "material.hh"
#include "controller.hh"

namespace GRand {
    class Mesh {
	private:
	    static Controller _static_defaultControler;
	    Core* _core;
	    Material& _material;
	    GPUBuffer _gb;
	    GLuint _glVertexArray;
	    Controller* _remote; 
	    std::vector<GLfloat> _vertexArray;
	    std::vector<GLuint> _elementArray;

	    void _getAllFaces(const struct aiScene *sc, const struct aiNode*);
	    void _render() const ;
	    void _uploadBuffer();
	public:
	    explicit Mesh(Core* e, Material&);
	    void set(const GPUBuffer&);
	    void fromFile(const std::string&);
	    Controller* genController();
	    Controller* getController();
	    void setExistantController(Controller*);
	    void setMaterial(Material& m_) { _material = m_; }
	    ~Mesh();
    };
}

#endif /* !MESH_H_ */
