#ifndef UNIFORM_H_
# define UNIFORM_H_
#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GL/gl.h>

// Uniform class is a class that represent a Opengl's shader uniform values
template <typename T>
class Uniform {
	private:
		T _value;
		GLint _location;
	public:
		// value is the default value, prgm the shader program, name the name of the value in the shader
		//nb: except if you are doing very spetial stuff just call Graphics::getCurentShader() to get GLuint prgm parametter 
		explicit Uniform(const T& value, GLuint prgm, const std::string& name) : _value(value), _location(glGetUniformLocation(prgm, name.c_str())) {
			if (_location == -1) {
				std::cout << "failed to bind location of uniform: \"" << name << "\"" << std::endl;
			}
		}
		explicit Uniform() : _value(T()), _location(0) {}
		explicit Uniform(const T& v_) : _value(v_), _location(0) {}
		void relocate(GLuint prgm, const std::string& name) { _location = glGetUniformLocation(prgm, name.c_str()); }
		void copyLocation(const Uniform<T>& o) { _location = o._location; }
		inline GLint getLct() const noexcept { return _location; }
		const Uniform<T>& operator=(const T& v) { _value = v; return *this; }
		const Uniform<T>& operator*(const T& v) { _value = v; return *this; }
		const Uniform<T>& operator/(const T& v) { _value = v; return *this; }
		const Uniform<T>& operator+(const T& v) { _value = v; return *this; }
		const Uniform<T>& operator-(const T& v) { _value = v; return *this; }
		T operator+=(const T& v) { _value += v; return _value; }
		T operator-=(const T& v) { _value -= v; return _value; }
		T operator*=(const T& v) { _value *= v; return _value; }
		T operator/=(const T& v) { _value /= v; return _value; }
		const Uniform<T>& operator++() { ++_value; }
		const Uniform<T>& operator--() { ++_value; }
		bool operator==(const T& v) { return _value == v._value; }
		bool operator!=(const T& v) { return _value != v._value; }
		bool operator<(const T& v) { return _value < v._value; }
		bool operator>(const T& v) { return _value > v._value; }
		bool operator<=(const T& v) { return _value <= v._value; }
		bool operator>=(const T& v) { return _value >= v._value; }
		const Uniform<T>& operator=(const T&& v) { _value = v; return *this; }
		const Uniform<T>& operator*(const T&& v) { _value = v; return *this; }
		const Uniform<T>& operator/(const T&& v) { _value = v; return *this; }
		const Uniform<T>& operator+(const T&& v) { _value = v; return *this; }
		const Uniform<T>& operator-(const T&& v) { _value = v; return *this; }
		void operator+=(const T&& v) { _value += v; }
		void operator-=(const T&& v) { _value -= v; }
		bool operator==(const T&& v) { return _value == v; }
		bool operator!=(const T&& v) { return _value != v; }
		bool operator<(const T&& v) { return _value < v; }
		bool operator>(const T&& v) { return _value > v; }
		bool operator<=(const T&& v) { return _value <= v; }
		bool operator>=(const T&& v) { return _value >= v; }
		T& operator>>(T&& v) { v = _value; return _value; }
		// if you need a member of _value or your operator is not binded you need to call this function 
		T& get() { return _value; }
		// this function update uniform value on GPU  (so usually need to call it before drawing polygons)
		virtual void upload() const;
};

#endif /* !UNIFORM_H_ */
