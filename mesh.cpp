#include "mesh.hh"

GRand::Mesh::Mesh(Core* e, Material* m) : _core(e), _material(m), _transform(Eigen::Matrix3f::Identity()) {
}

GRand::Mesh::~Mesh() {
}
