#include "sdmath/linear_algebra/matrix4x4.hpp"
#include "sdmath/linear_algebra/vector4.hpp"
#include <cstdlib>
#include <iostream>

static int Matrix4x4CorrectlyInitializesUsingVectorConstructor() {
	sdmath::Vector4 c0 = sdmath::Vector4(1,2,3,4);
	sdmath::Vector4 c1 = sdmath::Vector4(5,6,7,8);
	sdmath::Vector4 c2 = sdmath::Vector4(9,10,11,12);
	sdmath::Vector4 c3 = sdmath::Vector4(13,14,15,16);

	sdmath::Matrix4x4 matrix = sdmath::Matrix4x4(c0, c1, c2, c3);
	int error = 0;
	error += (matrix.col0 - c0).Magnitude();
	error += (matrix.col1 - c1).Magnitude();
	error += (matrix.col2 - c2).Magnitude();
	error += (matrix.col3 - c3).Magnitude();
	return std::abs(error);
}

static int Matrix4x4CorrectlyInitializesUsingElementsConstructorInColumnMajorOrder() {
	float r0c0 = 1.0f;
	float r0c1 = 2.0f;
	float r0c2 = 3.0f;
	float r0c3 = 4.0f;

	float r1c0 = 5.0f;
	float r1c1 = 6.0f;
	float r1c2 = 7.0f;
	float r1c3 = 8.0f;

	float r2c0 = 9.0f;
	float r2c1 = 10.0f;
	float r2c2 = 11.0f;
	float r2c3 = 12.0f;

	float r3c0 = 13.0f;
	float r3c1 = 14.0f;
	float r3c2 = 15.0f;
	float r3c3 = 16.0f;

	sdmath::Matrix4x4 matrix = sdmath::Matrix4x4(r0c0, r0c1, r0c2, r0c3, r1c0, r1c1, r1c2, r1c3, r2c0, r2c1, r2c2, r2c3, r3c0, r3c1, r3c2, r3c3);
	sdmath::Vector4 col0 = matrix.col0;
	sdmath::Vector4 col1 = matrix.col1;
	sdmath::Vector4 col2 = matrix.col2;
	sdmath::Vector4 col3 = matrix.col3;

	int error = 0;
	error += col0.x - r0c0;
	error += col0.y - r1c0;
	error += col0.z - r2c0;
	error += col0.w - r3c0;

	error += col1.x - r0c1;
	error += col1.y - r1c1;
	error += col1.z - r2c1;
	error += col1.w - r3c1;

	error += col2.x - r0c2;
	error += col2.y - r1c2;
	error += col2.z - r2c2;
	error += col2.w - r3c2;

	error += col3.x - r0c3;
	error += col3.y - r1c3;
	error += col3.z - r2c3;
	error += col3.w - r3c3;

	error = std::abs(error);
	if(error != 0) {
		std::cout << "ERROR, Initiaization of Matrix with element constructor does not produce the correct column major matrix \n";
	}
	return error;
}

static int Matrix4x4DefaultIsZeroMatrix() {
	sdmath::Matrix4x4 matrix = sdmath::Matrix4x4();
	int error = 0;
	error += matrix.col0.Magnitude();
	error += matrix.col1.Magnitude();
	error += matrix.col2.Magnitude();
	error += matrix.col3.Magnitude();
	return std::abs(error);
}

static int Matrix4x4Matrix4x4MultiplicationValid() {
	int error = 0;
	sdmath::Matrix4x4 matrix_a = sdmath::Matrix4x4(sdmath::Vector4(2,1,1,1), sdmath::Vector4(3,2,2,2), sdmath::Vector4(2,3,2,1), sdmath::Vector4(1,4,3,5));
	sdmath::Matrix4x4 matrix_b = sdmath::Matrix4x4(sdmath::Vector4(0.5f,1,10,1), sdmath::Vector4(2,9,9,2), sdmath::Vector4(2,0,5,1), sdmath::Vector4(2,5,3,5));
	sdmath::Matrix4x4 result = matrix_a * matrix_b;

	sdmath::Vector4 expected_col0 = sdmath::Vector4(25, 36.5f, 25.5f, 17.5f);
	sdmath::Vector4 expected_col1 = sdmath::Vector4(51, 55, 44, 39);
	sdmath::Vector4 expected_col2 = sdmath::Vector4(15, 21, 15, 12);
	sdmath::Vector4 expected_col3 = sdmath::Vector4(30, 41, 33, 40);

	sdmath::Vector4 actual_col0 = result.col0;
	sdmath::Vector4 actual_col1 = result.col1;
	sdmath::Vector4 actual_col2 = result.col2;
	sdmath::Vector4 actual_col3 = result.col3;

	std::cout << actual_col0.x << ", " << actual_col0.y << ", " << actual_col0.z << ", " << actual_col0.w << "\n";

	error += (actual_col0 - expected_col0).Magnitude();
	error += (actual_col1 - expected_col1).Magnitude();
	error += (actual_col2 - expected_col2).Magnitude();
	error += (actual_col3 - expected_col3).Magnitude();

	return error;
}

static int Matrix4x4LookAtConstructorGeneratesCorrectMatrix() {
	int error = 0;
	sdmath::Vector4 eye = sdmath::Vector4(0, 0, 0, 0);
	sdmath::Vector4 look_at = sdmath::Vector4(10,0,0,0);
	sdmath::Vector4 up = sdmath::Vector4(0,1,0,0);
	sdmath::Matrix4x4 matrix = sdmath::Matrix4x4::LookAt(eye, look_at, up);
	sdmath::Matrix4x4 obj_original = sdmath::Matrix4x4::Identity();

	sdmath::Matrix4x4 obj_view_space = matrix * obj_original;

	sdmath::Vector4 expected_right = 	sdmath::Vector4(0,0,1,0);
	sdmath::Vector4 expected_forward = sdmath::Vector4(1,0,0,0);
	sdmath::Vector4 actual_right = obj_view_space.col0;
	sdmath::Vector4 actual_up = obj_view_space.col1;
	sdmath::Vector4 actual_forward = obj_view_space.col2;
	error += (actual_right - expected_right).Magnitude();
	error += (actual_forward - expected_forward).Magnitude();
	error += (actual_up - up).Magnitude();

	sdmath::Vector4 actual_position = obj_view_space.col3;
	sdmath::Vector4 expected_position = sdmath::Vector4(0,0,0,1);

	error += (actual_position - expected_position).Magnitude();
	
	return error;
}

//Perspective division happens in the shader itself, when we set the gl_position variable, divides everything by the z coordinate of the vector4, so we are omiting that here
static int Matrix4x4PerspectiveConstructorGeneratesCorrectMatrix() {
	int error = 0;
	float field_of_view = 30;
	int width = 1920;
	int height = 1080;
	float near_clipping_plane = 0.1f;
	float far_clipping_plane = 1000.0f;
	sdmath::Matrix4x4 perspective_matrix = sdmath::Matrix4x4::Perspective(height, width, field_of_view, near_clipping_plane, far_clipping_plane);
	sdmath::Vector4 col0 = perspective_matrix.col0;
	sdmath::Vector4 col1 = perspective_matrix.col1;
	sdmath::Vector4 col2 = perspective_matrix.col2;
	sdmath::Vector4 col3 = perspective_matrix.col3;

	sdmath::Vector4 correct_col0 = sdmath::Vector4(-0.65713f, 0, 0, 0);
	sdmath::Vector4 correct_col1 = sdmath::Vector4(0, -1.16823f, 0, 0);
	sdmath::Vector4 correct_col2 = sdmath::Vector4(0, 0, 0.9f, 1);
	sdmath::Vector4 correct_col3 = sdmath::Vector4(0, 0, -0.10001f, 0);

	error += (col0 - correct_col0).Magnitude();
	error += (col1 - correct_col1).Magnitude();
	error += (col2- correct_col2).Magnitude();
	error += (col3 - correct_col3).Magnitude();
	return error;
}

static int Matrix4x4IdentityIsIdentityMatrix() {
	sdmath::Matrix4x4 identity = sdmath::Matrix4x4::Identity();
	int diagonal0 = identity.col0.x;
	int diagonal1 = identity.col1.y;
	int diagonal2 = identity.col2.z;
	int diagonal3 = identity.col3.w;
	int correct_diagonal_value = 1;

	int error = 0;
	error += diagonal0 - correct_diagonal_value;
	error += diagonal1 - correct_diagonal_value;
	error += diagonal2 - correct_diagonal_value;
	error += diagonal3 - correct_diagonal_value;
	return std::abs(error);
}

int main (int argc, char *argv[]) {
	int error = 0;
	error += Matrix4x4CorrectlyInitializesUsingVectorConstructor();
	error += Matrix4x4CorrectlyInitializesUsingElementsConstructorInColumnMajorOrder();
	error += Matrix4x4DefaultIsZeroMatrix();
	error += Matrix4x4IdentityIsIdentityMatrix();
	error += Matrix4x4Matrix4x4MultiplicationValid();
	error += Matrix4x4LookAtConstructorGeneratesCorrectMatrix();
	error += Matrix4x4PerspectiveConstructorGeneratesCorrectMatrix();
	return error;
}
