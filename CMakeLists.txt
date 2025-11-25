cmake_minimum_required(VERSION 3.6...3.14 FATAL_ERROR)
cmake_policy(VERSION 3.6...3.14)

project(sdmath)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_FILES 
	src/linear_algebra/vector4.cpp
)

add_library(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(
  ${PROJECT_NAME} 
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(
  ${PROJECT_NAME} 
)

#TODO: Add support for other compilers
#This assumes you're using GCC, we need this to enable AVX2 instructions
target_compile_options(${PROJECT_NAME} PRIVATE -march=native -mavx2 -O3)

#This part is inspired by the glm library, the way they handle tests relies on no external dependencies, and is 
#pretty easy to work with
option(SDMATH_COMPILE_UNIT_TESTS "Compiles the unit tests" ON)

if(SDMATH_COMPILE_UNIT_TESTS)
	include(CTest)
	add_subdirectory(test)
	message("-- Unit tests enabled")
endif()

