cmake_minimum_required(VERSION 2.0)

project(HellmanCompiler CXX)

find_package(FLEX)
FLEX_TARGET(flexThing language_0.l ${CMAKE_CURRENT_BINARY_DIR}/language_0.cpp)

include_directories(".")

add_definitions(
	-std=c++11
)

add_executable(frontend
	frontend.cpp
	tokenstream.cpp
	${FLEX_flexThing_OUTPUTS}

	token.hpp
	tokenstream.hpp
)
target_link_libraries(frontend fl)
