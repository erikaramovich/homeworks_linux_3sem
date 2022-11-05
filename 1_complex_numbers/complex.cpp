#include "complex.h"
#include <cmath>

// constructor
Complex::Complex(float x, float y): a(x), b(y) {}

// destructor
Complex::~Complex() {}

// calculating absolute value
float Complex::abs()const {
	float x = a * a;
	float y = b * b;
	x += y;

	return sqrt(x);
}

// overloading operator<< for Complex objects
std::ostream& operator<<(std::ostream& out,const Complex& obj){
	out << "{" << obj.a << " + " << obj.b << "i}" << std::endl;
	return out;
}

// define + operation on Complex numbers
Complex Complex::operator+(const Complex& other) const{
	Complex result(a + other.a, b + other.b);
	return result;
}

// define - operation on Complex numbers
Complex Complex::operator-(const Complex& other) const{
	Complex result(a - other.a, b - other.b);
	return result;
}

// define *by constant on Complex numbers
Complex Complex::operator*(float x) const{
	Complex result(a * x, b * x);
	return result;
}



