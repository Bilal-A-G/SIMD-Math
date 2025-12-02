#include "sdmath/linear_algebra/vector4.hpp"
#include <iostream>

static int Vector4InitTest() {
	int error = 0;
	sdmath::Vector4 vec4 = sdmath::Vector4(1,1,1,1);

	error += vec4.x != 1 ? 1 : 0;
	error += vec4.y != 1 ? 1 : 0;
	error += vec4.z != 1 ? 1 : 0;
	error += vec4.w != 1 ? 1 : 0;

	return error;
}

static int Vector4SubtractionValid() {
	sdmath::Vector4 a = sdmath::Vector4(1,1,1,1);
	sdmath::Vector4 b = sdmath::Vector4(2,3,4,5);

	sdmath::Vector4 result = b - a;
	sdmath::Vector4 correct = sdmath::Vector4(1,2,3,4);
	int error = 0;
	error += result.x - correct.x;
	error += result.y - correct.y;
	error += result.z - correct.z;
	error += result.w - correct.w;

	if(error != 0) {
		std::cout << "Error, Vector4-Vector4 subtraction does not result in the correct answer! \n";
		return std::abs(error);
	}

	sdmath::Vector4 result_reversed = a - b;
	sdmath::Vector4 correct_reversed = sdmath::Vector4(-1,-2,-3,-4);
	error += result_reversed.x - correct_reversed.x;
	error += result_reversed.y - correct_reversed.y;
	error += result_reversed.z - correct_reversed.z;
	error += result_reversed.w - correct_reversed.w;

	if(error != 0) {
		std::cout << "Error, Vector4-Vector4 subtraction does not respect the order of vectors being subtracted! \n";
	}
	return error;
}

static int Vector4MagnitudeValid() {
	sdmath::Vector4 vector = sdmath::Vector4(1,2,3,4);
	float correct = 5.477225575f;
	float delta = 0.000000001f;
	return std::abs(correct - vector.Magnitude()) > delta ? 1:0;
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

static int Vector4DotIsValid() {
	int error = 0;
	sdmath::Vector4 a = sdmath::Vector4(1,2,3,4);
	sdmath::Vector4 b = sdmath::Vector4(1,2,0,0);
	float result = a.Dot(b);
	float expected_result = 5;
	return std::abs(expected_result - result);
}

static int Vector4ScalarDivisionIsValid() {
	int error = 0;
	sdmath::Vector4 a = sdmath::Vector4(4,2,2,2);
	float divisor = 2;
	sdmath::Vector4 result = a/divisor;
	float expected_x = 2;
	float expected_rest = 1;
	error += result.x - expected_x;
	error += result.y - expected_rest;
	error += result.z - expected_rest;
	error += result.w - expected_rest;

	return error;
}

static int Vector4NormalizationIsValid() {
	int error = 0;
	sdmath::Vector4 a = sdmath::Vector4(100,0,0,0);
	sdmath::Vector4 normalized = a.Normalize();
	sdmath::Vector4 expected_normalized = sdmath::Vector4(1,0,0,0);
	error += (normalized - expected_normalized).Magnitude();

	return error;
}

//Note, vector4 cross just computes the cross product of the first 3 elements, it ignores the w component, as 
//the cross product is not defined in 4d
static int Vector4CrossIsValid() {
	int error = 0;
	sdmath::Vector4 a = sdmath::Vector4(1,1,0,0);
	sdmath::Vector4 b = sdmath::Vector4(2,2,2,0);
	sdmath::Vector4 expected_result = sdmath::Vector4(2,-2,-0.2f,0);
	sdmath::Vector4 actual_result = a.Cross(b);
	error += (actual_result - expected_result).Magnitude();
	return error;
}

int main (int argc, char *argv[]) {
	int error = 0;
	error += Vector4InitTest();
	error += Vector4AddTest();
	error += Vector4SubtractionValid();
	error += Vector4MagnitudeValid();
	error += Vector4DotIsValid();
	error += Vector4ScalarDivisionIsValid();
	error += Vector4NormalizationIsValid();
	error += Vector4CrossIsValid();
	return error;
}
