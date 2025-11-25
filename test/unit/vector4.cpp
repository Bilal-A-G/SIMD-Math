#include "sdmath/linear_algebra/vector4.hpp"

static int Vector4InitTest() {
	int error = 0;
	sdmath::Vector4 vec4 = sdmath::Vector4(1,1,1,1);

	error += vec4.x != 1 ? 1 : 0;
	error += vec4.y != 1 ? 1 : 0;
	error += vec4.z != 1 ? 1 : 0;
	error += vec4.w != 1 ? 1 : 0;

	return error;
}

static int Vector4AddTest() {
	int error = 0;
	sdmath::Vector4 a = sdmath::Vector4(1,1,1,1);
	sdmath::Vector4 b = sdmath::Vector4(2,2,2,2);

	sdmath::Vector4 result = a + b;
	float correct_answer = 3; 

	error += result.x != correct_answer ? 1 : 0;
	error += result.y != correct_answer ? 1 : 0;
	error += result.z != correct_answer ? 1 : 0;
	error += result.w != correct_answer ? 1 : 0;

	return error;
}

int main (int argc, char *argv[]) {
	int error = 0;
	error += Vector4InitTest();
	error += Vector4AddTest();
	return error;
}
