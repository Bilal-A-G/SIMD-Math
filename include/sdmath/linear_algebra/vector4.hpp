#ifndef SIMDMATH_LINEAR_ALGEBRA_VECTOR4_H
#define SIMDMATH_LINEAR_ALGEBRA_VECTOR4_H
#include <immintrin.h>
namespace sdmath {
struct Vector4 {
public:	
	Vector4(float x = 0, float y = 0, float z = 0, float w = 0); 
	Vector4 operator +(Vector4& other);
	//TODO: Make this have a non-simd version, make some kind of macro so we don't have to keep redoing the tests, it's very tedious, ie so
	//we don't have duplicate tests for this and the non-simd version
	Vector4 operator -(Vector4& other);
	Vector4 Add_NOSD(Vector4& other);
	float Magnitude();
	//Make this work, vector simd vector add on an array of arbitrary data with vectors in it,
	//where the vectors are defined at every stride + sizeof(Vector4), starting at the offset
	//AddVectors(void* data, int offset, int stride, int size, std::vector<Vector4> other);
public:
	float x, y, z, w;
};
}
#endif
