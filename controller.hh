#ifndef CONTROLLER_H_
# define CONTROLLER_H_

#include <glm/glm.hpp>
#include "uniform.hh"

namespace GRand {
    class Controller {
	private:
	    typedef glm::mat4 MatType;
	    typedef glm::vec3 VectorType;
	    Uniform<glm::mat4> _utrans;
	public:
	    explicit Controller();
	    void translate(const VectorType&);
	    void rotate(float, const VectorType&);
	    void scale(const VectorType&);
	    void setUniform(const decltype(_utrans)&);
	    void refresh();
    };
}

#endif /* !CONTROLLER_H_ */
