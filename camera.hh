#ifndef CAMERA_H_
# define CAMERA_H_

#include <eigen3/Eigen/Dense>
#include "core.hh"
#include "uniform.hh"

namespace GRand {
    class Camera {
	public:
	    typedef Eigen::Matrix4f matType ;
	private:
	    Core* _core;
	    Uniform<matType> _utrans;
	    Eigen::Vector3f _center;
	    Eigen::Vector3f _target;
	    void _refresh();
	public:
	    explicit Camera(Core*);
	    void translate(const Eigen::Vector3f&);
	    void lookAt(const Eigen::Vector3f&);
    };
}

#endif /* !CAMERA_H_ */
