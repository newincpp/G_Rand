#ifndef MESH_H_
# define MESH_H_

#include <eigen3/Eigen/Dense>
#include "core.hh"
#include "material.hh"

namespace GRand {
    class Mesh {
	private:
	    Core* _core;
	    Material* _material;
	    Eigen::Matrix3f _transform;
	    GPUBuffer _gb;
	    void _render();
	public:
	    explicit Mesh(Core* e, Material*);
	    ~Mesh();
    };
}

#endif /* !MESH_H_ */
