#ifndef EIGENUTILITY_H_
# define EIGENUTILITY_H_

#include <iostream>
#include <eigen3/Eigen/Core>

template<class T>
Eigen::Matrix<T,4,4> perspective(double fovy, double aspect, double zNear, double zFar) {
    typedef Eigen::Matrix<T,4,4> Matrix4;

    assert(aspect > 0);
    assert(zFar > zNear);

    double tanHalfFovy = tan(fovy/ 2.0);
    Matrix4 res = Matrix4::Zero();
    res(0,0) = 1.0 / (aspect * tanHalfFovy);
    res(1,1) = 1.0 / (tanHalfFovy);
    res(2,2) = - (zFar + zNear) / (zFar - zNear);
    res(3,2) = - 1.0;
    res(2,3) = - (2.0 * zFar * zNear) / (zFar - zNear);
    return res;
}

//template<class T>
//Eigen::Matrix<T,4,4> lookAt(Eigen::Matrix<T,3,1> const & eye, Eigen::Matrix<T,3,1> const & center, Eigen::Matrix<T,3,1> const & up) {
//    typedef Eigen::Matrix<T,4,4> Matrix4;
//    typedef Eigen::Matrix<T,3,1> Vector3;
//
//    Vector3 f = (center - eye).normalized();
//    Vector3 u = up.normalized();
//    Vector3 s = f.cross(u).normalized();
//    u = s.cross(f);
//
//    Matrix4 res;
//    res <<  s.x(),s.y(),s.z(),-s.dot(eye),
//	u.x(),u.y(),u.z(),-u.dot(eye),
//	-f.x(),-f.y(),-f.z(),f.dot(eye),
//	0,0,0,1;
//    res.transposeInPlace();
//
//    return res;
//}

template<typename Scalar>
Eigen::Matrix<Scalar,4,4> lookAt(const Eigen::Matrix<Scalar, 3 , 1> & eye, const Eigen::Matrix<Scalar, 3 , 1>& center, const Eigen::Matrix<Scalar, 3 , 1>& up){
    typedef Eigen::Matrix<Scalar,4,4> Matrix4;
    typedef Eigen::Matrix<Scalar,3,1> Vector3;
    Vector3 f = (center - eye).normalized();
    Vector3 u = up.normalized();
    Vector3 s = f.cross(u).normalized();
    u = s.cross(f);
    Matrix4 mat = Matrix4::Zero();
    mat(0,0) = s.x();
    mat(0,1) = s.y();
    mat(0,2) = s.z();
    mat(0,3) = -s.dot(eye);
    mat(1,0) = u.x();
    mat(1,1) = u.y();
    mat(1,2) = u.z();
    mat(1,3) = -u.dot(eye);
    mat(2,0) = -f.x();
    mat(2,1) = -f.y();
    mat(2,2) = -f.z();
    mat(2,3) = f.dot(eye);
    mat.row(3) << 0,0,0,1; 
    mat.transposeInPlace();
    std::cout << mat << std::endl;
    return mat;
}

#endif /* !EIGENUTILITY_H_ */
