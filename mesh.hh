#ifndef MESH_H_
# define MESH_H_

#include "core.hh"
#include "material.hh"

namespace GRand {
    class Mesh {
	private:
	    Core* _core;
	    Material* _material;
	    void _render();
	public:
	    explicit Mesh(Core* e, Material*);
	    ~Mesh();
    };
}

#endif /* !MESH_H_ */
