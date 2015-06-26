#ifndef CAMERA_H_
# define CAMERA_H_

#include <glm/glm.hpp>
#include "core.hh"
#include "uniform.hh"

namespace GRand {
    class Camera {
	public:
	    typedef glm::mat4 MatType;
	    typedef glm::vec3 VectorType;
	private:
	    Core* _core;
	    Uniform<MatType> _utrans;
	    VectorType _center;
	    VectorType _target;
	    void _refresh();
	public:
	    explicit Camera(Core*);
	    void translate(const VectorType&);
	    void setPos(const VectorType&);
	    void lookAt(const VectorType&);
    };
}

#endif /* !CAMERA_H_ */
