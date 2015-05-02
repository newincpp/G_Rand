#ifndef CONTROLLER_H_
# define CONTROLLER_H_

#include <eigen3/Eigen/Dense>

namespace GRand {
    class Controller {
	private:
	    Eigen::Matrix3f& _transform;
	public:
	    explicit Controller(Eigen::Matrix3f&);
    };
}

#endif /* !CONTROLLER_H_ */