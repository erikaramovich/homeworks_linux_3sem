#ifndef COMPLEX_H
#define COMPLEX_H
#include <iostream>

// Complex numbers looks like (a + bi)
class Complex
{
private:
	float a;
	float b;
public:
	Complex(float=1, float=1);
	~Complex();
	float abs()const;
	Complex operator+(const Complex&)const;
	Complex operator-(const Complex&)const;
	Complex operator*(float)const;
	friend std::ostream& operator<<(std::ostream&, const Complex&);
};


#endif
