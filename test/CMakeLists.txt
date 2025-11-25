option(SDMATH_COMPILE_PERF_TESTS "Compiles the performnance tests" ON)

function(SDMATH_CREATE_TEST NAME)
	set(EXECUTABLE_NAME test-${NAME})
	add_executable(${EXECUTABLE_NAME} ${NAME}.cpp)
	add_test(
		NAME ${EXECUTABLE_NAME}
		COMMAND $<TARGET_FILE:${EXECUTABLE_NAME}>)
	target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${PROJECT_NAME})
	#TODO: Add support for other compilers
	#This assumes you're using GCC, we need this to enable AVX2 instructions
	target_compile_options(${EXECUTABLE_NAME} PRIVATE -march=native -mavx2 -O3)
endfunction()

if(SDMATH_COMPILE_PERF_TESTS)
	message("-- Performance tests enabled")
	add_subdirectory(perf)
endif()

add_subdirectory(unit)
