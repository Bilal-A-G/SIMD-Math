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
