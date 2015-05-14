#ifndef CONTROLLER_H_
# define CONTROLLER_H_

#include <eigen3/Eigen/Dense>
#include "uniform.hh"

namespace GRand {
    class Controller {
	private:
	    Eigen::Affine3f _transform;
	    Uniform<Eigen::Matrix4f> _utrans;
	public:
	    explicit Controller();
	    void translate(const Eigen::Vector3f&);
	    void rotate(float, const Eigen::Vector3f&);
	    void scale(const Eigen::Vector3f&);
	    void setUniform(const decltype(_utrans)&);
	    void refresh();
    };
}

#endif /* !CONTROLLER_H_ */
