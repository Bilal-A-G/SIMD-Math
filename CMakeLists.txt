cmake_minimum_required(VERSION 3.9)

project(SIMDMath)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_FILES 
	src/linear_algebra/vector4.cpp
)

add_library(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(
  ${PROJECT_NAME} 
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
  ${PROJECT_NAME} 
)
