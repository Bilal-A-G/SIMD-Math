#include "sdmath/linear_algebra/vector4.hpp"
#include "immintrin.h"

sdmath::Vector4::Vector4(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

sdmath::Vector4 sdmath::Vector4::operator+(sdmath::Vector4& other) {
	//4 floats worth of space wasted :(
	__m128 a = _mm_loadu_ps((float*)&other);
	__m128 b = _mm_loadu_ps((float*)this);

	__m128 result = _mm_add_ps(a, b);
	float* as_float = (float*)&result;

	Vector4 to_return = Vector4();
	_mm_storeu_ps((float*)&to_return, result);
	return to_return;
}

sdmath::Vector4 sdmath::Vector4::Add_NOSD(sdmath::Vector4& other) {
	sdmath::Vector4 res = sdmath::Vector4();
	res.x = other.x + x;
	res.y = other.y + y;
	res.z = other.z + z;
	res.w = other.w + w;
	return res;
}
