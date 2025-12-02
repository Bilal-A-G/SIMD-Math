#include "sdmath/linear_algebra/vector4.hpp"
#include "immintrin.h"
#include <cmath>
#include <xmmintrin.h>

sdmath::Vector4::Vector4(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

sdmath::Vector4 sdmath::Vector4::operator+(sdmath::Vector4& other) {
	__m128 a = _mm_loadu_ps((float*)&other);
	__m128 b = _mm_loadu_ps((float*)this);

	__m128 result = _mm_add_ps(a, b);
	Vector4 to_return = Vector4();
	_mm_storeu_ps((float*)&to_return, result);
	return to_return;
}

sdmath::Vector4 sdmath::Vector4::operator-(sdmath::Vector4& other) {
	__m128 a = _mm_loadu_ps((float*)&other);
	__m128 b = _mm_loadu_ps((float*)this);

	__m128 result = _mm_sub_ps(b, a);
	Vector4 to_return = Vector4();
	_mm_storeu_ps((float*)&to_return, result);
	return to_return;
}

float sdmath::Vector4::Magnitude() {
	return std::sqrt(std::pow(x, 2.0f) + std::pow(y, 2.0f) + std::pow(z, 2.0f) + std::pow(w, 2.0f));
}

sdmath::Vector4 sdmath::Vector4::Add_NOSD(sdmath::Vector4& other) {
	sdmath::Vector4 res = sdmath::Vector4();
	res.x = other.x + x;
	res.y = other.y + y;
	res.z = other.z + z;
	res.w = other.w + w;
	return res;
}

float sdmath::Vector4::Dot(sdmath::Vector4& other) {
	return x * other.x + y * other.y + z * other.z + w * other.w;
}

//Calculated via the cofactor expansion method detailed here: https://www.wikihow.com/Calculate-the-Cross-Product-of-Two-Vectors
sdmath::Vector4 sdmath::Vector4::Cross(sdmath::Vector4& other) {
	return sdmath::Vector4(y * other.z - other.y * z, -(x * other.z - other.x * z), x * other.y - other.x * y, other.w);
}

sdmath::Vector4 sdmath::Vector4::operator/(float& other) {
	return sdmath::Vector4(x/other, y/other, z/other, w/other);
}

sdmath::Vector4 sdmath::Vector4::operator/(float&& other) {
	return sdmath::Vector4(x/other, y/other, z/other, w/other);
}

sdmath::Vector4 sdmath::Vector4::Normalize() {
	sdmath::Vector4 to_return = sdmath::Vector4(x,y,z,w);
	to_return = to_return/to_return.Magnitude();
	return to_return;
}
