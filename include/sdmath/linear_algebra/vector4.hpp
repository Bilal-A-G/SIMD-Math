#include <immintrin.h>
namespace sdmath {
#ifndef SIMDMATH_LINEAR_ALGEBRA_VECTOR4_H
#define SIMDMATH_LINEAR_ALGEBRA_VECTOR4_H
struct Vector4 {
public:	
	Vector4(float x = 0, float y = 0, float z = 0, float w = 0); 
	Vector4 operator +(Vector4& other);
	Vector4 Add_NOSD(Vector4& other);
	//Make this work, vector simd vector add on an array of arbitrary data with vectors in it,
	//where the vectors are defined at every stride + sizeof(Vector4), starting at the offset
	//AddVectors(void* data, int offset, int stride, int size, std::vector<Vector4> other);
public:
	float x, y, z, w;
};
#endif
}
