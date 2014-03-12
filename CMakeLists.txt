cmake_minimum_required(VERSION 2.0)

project(HellmanCompiler CXX)

find_package(FLEX)
FLEX_TARGET(flexScanner language_0.l ${CMAKE_CURRENT_BINARY_DIR}/language_0.cpp)

# TODO: Organize files
include_directories(".")

add_definitions(
	-std=c++11
)

add_executable(frontend
	token.hpp
	token.cpp

	frontend.cpp

	${FLEX_flexScanner_OUTPUTS}
)
target_link_libraries(frontend fl)
