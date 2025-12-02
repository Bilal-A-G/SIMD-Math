#include "sdmath/linear_algebra/matrix4x4.hpp"
#include "sdmath/linear_algebra/vector4.hpp"

//TODO: Load the data into the class in a more optimal way, we can use SIMD for this
sdmath::Matrix4x4::Matrix4x4(
		float r0c0, float r0c1, float r0c2, float r0c3,
		float r1c0, float r1c1, float r1c2, float r1c3,
		float r2c0, float r2c1, float r2c2, float r2c3,
		float r3c0, float r3c1, float r3c2, float r3c3) {
	this->col0 = Vector4(r0c0, r1c0, r2c0, r3c0);
	this->col1 = Vector4(r0c1, r1c1, r2c1, r3c1);
	this->col2 = Vector4(r0c2, r1c2, r2c2, r3c2);
	this->col3 = Vector4(r0c3, r1c3, r2c3, r3c3);
}

sdmath::Matrix4x4::Matrix4x4(Vector4 col0, Vector4 col1, Vector4 col2, Vector4 col3) {
	this->col0 = col0;	
	this->col1 = col1;	
	this->col2 = col2;	
	this->col3 = col3;	
}

sdmath::Matrix4x4 sdmath::Matrix4x4::Identity() {
	sdmath::Vector4 identity_c0 = sdmath::Vector4(1,0,0,0);
	sdmath::Vector4 identity_c1 = sdmath::Vector4(0,1,0,0);
	sdmath::Vector4 identity_c2 = sdmath::Vector4(0,0,1,0);
	sdmath::Vector4 identity_c3 = sdmath::Vector4(0,0,0,1);
	return sdmath::Matrix4x4(identity_c0, identity_c1, identity_c2, identity_c3);
}

//TODO: Do SIMD for this operation
sdmath::Matrix4x4 sdmath::Matrix4x4::operator*(sdmath::Matrix4x4& other) {
	sdmath::Matrix4x4 output = sdmath::Matrix4x4();
	sdmath::Vector4 a_row0 = sdmath::Vector4(this->col0.x, this->col1.x, this->col2.x, this->col3.x);
	sdmath::Vector4 a_row1 = sdmath::Vector4(this->col0.y, this->col1.y, this->col2.y, this->col3.y);
	sdmath::Vector4 a_row2 = sdmath::Vector4(this->col0.z, this->col1.z, this->col2.z, this->col3.z);
	sdmath::Vector4 a_row3 = sdmath::Vector4(this->col0.w, this->col1.w, this->col2.w, this->col3.w);

	output.col0.x = a_row0.Dot(other.col0);
	output.col1.x = a_row0.Dot(other.col1);
	output.col2.x = a_row0.Dot(other.col2);
	output.col3.x = a_row0.Dot(other.col3);

	output.col0.y = a_row1.Dot(other.col0);
	output.col1.y = a_row1.Dot(other.col1);
	output.col2.y = a_row1.Dot(other.col2);
	output.col3.y = a_row1.Dot(other.col3);

	output.col0.z = a_row2.Dot(other.col0);
	output.col1.z = a_row2.Dot(other.col1);
	output.col2.z = a_row2.Dot(other.col2);
	output.col3.z = a_row2.Dot(other.col3);

	output.col0.w = a_row3.Dot(other.col0);
	output.col1.w = a_row3.Dot(other.col1);
	output.col2.w = a_row3.Dot(other.col2);
	output.col3.w = a_row3.Dot(other.col3);

	return output;
}

//Formula for the look at matrix comes from: https://learnopengl.com/Getting-Started/Camera
//The reason for using dot products in the translation component is described here: https://stackoverflow.com/questions/349050/calculating-a-lookat-matrix
sdmath::Matrix4x4 sdmath::Matrix4x4::LookAt(Vector4 &eye, Vector4 &center, Vector4 &up) {
	sdmath::Matrix4x4 look_at_matrix = sdmath::Matrix4x4();
	sdmath::Vector4 forward = (center - eye).Normalize();
	sdmath::Vector4 right = forward.Cross(up).Normalize();
	sdmath::Vector4 inverse_translation = sdmath::Vector4(-eye.x, -eye.y, -eye.z, 1);

	look_at_matrix.col0 = sdmath::Vector4(right.x, up.x, forward.x, 0.0f);
	look_at_matrix.col1 = sdmath::Vector4(right.y, up.y, forward.y, 0.0f);
	look_at_matrix.col2 = sdmath::Vector4(right.z, up.z, forward.z, 0.0f);
	look_at_matrix.col3 = sdmath::Vector4(right.Dot(inverse_translation), up.Dot(inverse_translation), forward.Dot(inverse_translation), inverse_translation.w);
	return look_at_matrix;
}
