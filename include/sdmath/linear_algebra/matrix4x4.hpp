#ifndef SIMDMATH_LINEAR_ALGEBRA_MATRIX4X4_H
#define SIMDMATH_LINEAR_ALGEBRA_MATRIX4X4_H
#include "sdmath/linear_algebra/vector4.hpp"
namespace sdmath {
//Represents a column major 4 x 4 matrix, composed of 4 vector4s, where each vector represents a column of the matrix
struct Matrix4x4 {
public:
	Matrix4x4(Vector4 col0, Vector4 col1, Vector4 col2, Vector4 col3);
	/*
	 	Matrix initialization order
		|R0C0|R0C1|R0C2|R0C3|
		|R1C0|R1C1|R1C2|R1C3|
		|R2C0|R2C1|R2C2|R2C3|
		|R3C0|R3C1|R3C2|R3C3|
	*/
	Matrix4x4(
		float r0c0, float r0c1, float r0c2, float r0c3,
		float r1c0, float r1c1, float r1c2, float r1c3,
		float r2c0, float r2c1, float r2c2, float r2c3,
		float r3c0, float r3c1, float r3c2, float r3c3
	);
	//Constructs a zero matrix
	Matrix4x4() = default;
	static Matrix4x4 Identity();
	//TODO: Maybe move the look at and perspective "constructors" into a different class just for matrix transformations, like GLM
	/*
	 Eye = position of the viewer
	 Center = position being looked at
	 Up = up vector
	*/
	static Matrix4x4 LookAt(Vector4& eye, Vector4& center, Vector4& up);
	//TODO: Some kind of indication for unit, radians or degrees
	static Matrix4x4 Perspective(int height, int width, float field_of_view, float near_plane, float far_plane);

	Matrix4x4 operator *(Matrix4x4& other);
public:
	Vector4 col0;
	Vector4 col1;
	Vector4 col2;
	Vector4 col3;
};
}
#endif
