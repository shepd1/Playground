#pragma once
#include <ostream>
#include <math.h>

class Vec3f
{
	friend std::ostream& operator << (std::ostream& o, const Vec3f& v);
	friend Vec3f operator * (float s, Vec3f& v);

private:
	float _a;
	float _b;
	float _c;

public:

	// Constructors

	Vec3f::Vec3f(float a = 0, float b = 0, float c = 0) : _a(a), _b(b), _c(c)
	{
	}

	Vec3f::Vec3f(float v[3]) : _a(v[0]), _b(v[1]), _c(v[2])
	{
	}
	
	Vec3f::~Vec3f() {}

	//--------------------------

	// Operators

	Vec3f Vec3f::operator - () 
	{
		Vec3f result;

		result._a = -this->_a;
		result._b = -this->_b;
		result._c = -this->_c;

		return result;
	}

	Vec3f Vec3f::operator + (const Vec3f& v)
	{
		Vec3f result;

		result._a = this->_a + v._a;
		result._b = this->_b + v._b;
		result._c = this->_c + v._c;

		return result;
	}

	float Vec3f::operator * (const Vec3f& v)	//Dot product
	{
		float result;

		result= this->_a * v._a + this->_b * v._b + this->_c * v._c;

		return result;
	}

	Vec3f Vec3f::operator - (const Vec3f& v)
	{
		Vec3f result;

		result._a = this->_a - v._a;
		result._b = this->_b - v._b;
		result._c = this->_c - v._c;

		return result;
	}

	Vec3f Vec3f::operator /= (const float n)
	{
		this->_a = this->_a / n;
		this->_b = this->_b / n;
		this->_c = this->_c / n;

		return *this;
	}

	int Vec3f::operator == (const Vec3f& v)
	{
		if (this->_a == v._a && this->_b == v._b && this->_c == v._c)
		{
			return 1;
		}
		return 0;
	}

	Vec3f Vec3f::operator ^ (const Vec3f& v)
	{
		Vec3f result;

		result._a = (this->_b * v._c) - (this->_c * v._b);
		result._b = (this->_c * v._a) - (this->_a * v._c);
		result._c = (this->_a * v._b) - (this->_b * v._a);
		
		return result;
	}

	//-------------------------------

	// Functions

	Vec3f Vec3f::normalize()
	{
		*this /= this->length();

		return *this;
	}

	float Vec3f::length()
	{
		Vec3f v;
		v._a = powf(this->_a, 2.0f);
		v._b = powf(this->_b, 2.0f);
		v._c = powf(this->_c, 2.0f);

		return sqrtf(v._a + v._b + v._c);
	}

	//---------------------------
};

std::ostream& operator << (std::ostream& o, const Vec3f& v)
{
	o << "(" << v._a << ", " << v._b << ", " << v._c << ")";
	
	return o;
}

Vec3f operator * (const float s, Vec3f& v)	//Scalar * Vector
{
	Vec3f result; 

	result._a = v._a * s;
	result._b = v._b * s;
	result._c = v._c * s;

	return result;
}

