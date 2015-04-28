#ifndef MESH_H_
# define MESH_H_

#include <eigen3/Eigen/Dense>
#include "GPUBuffer.hh"
#include "core.hh"
#include "material.hh"

namespace GRand {
    class Mesh {
	private:
	    Core* _core;
	    Material* _material;
	    Eigen::Matrix3f _transform;
	    GPUBuffer _gb;
	    void _render() const noexcept;
	public:
	    explicit Mesh(Core* e, Material*);
	    void set(const GPUBuffer&);
	    ~Mesh();
    };
}

#endif /* !MESH_H_ */
