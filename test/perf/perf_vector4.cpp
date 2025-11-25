#include "sdmath/linear_algebra/vector4.hpp"
#include <chrono>
#include <iostream>

static void Vector4AddTestPerformance() {
	sdmath::Vector4 a = sdmath::Vector4(1,1,1,1);
	sdmath::Vector4 b = sdmath::Vector4(1,1,1,1);
	int iterations = 100'000'000;
	volatile float sink = 0;
	
	auto sd_start = std::chrono::high_resolution_clock::now();
	for(int i = 0; i < iterations; i++) {
		sdmath::Vector4 c = b + a;
		sink += c.x;
	}
	auto sd_end = std::chrono::high_resolution_clock::now();
	auto sd_duration = std::chrono::duration_cast<std::chrono::milliseconds>(sd_end - sd_start);
	std::cout << "Result (With SIMD) took " << sd_duration.count() << "ms with " << iterations << "\n";

	sink = 0;
	auto non_sd_start = std::chrono::high_resolution_clock::now();
	for(int i = 0; i < iterations; i++) {
		sdmath::Vector4 c = b.Add_NOSD(a);
		sink += c.x;
	}
	auto non_sd_end = std::chrono::high_resolution_clock::now();
	auto non_sd_duration = std::chrono::duration_cast<std::chrono::milliseconds>(non_sd_end - non_sd_start);
	std::cout << "Result (Without SIMD) took " << non_sd_duration.count() << "ms with " << iterations << "\n";
}

int main (int argc, char *argv[]) {
	Vector4AddTestPerformance();
	return 0;
}
