cmake_minimum_required(VERSION 2.0)

project(HellmanCompiler)

find_package(FLEX)
FLEX_TARGET(flexThing language_0.lex ${CMAKE_CURRENT_BINARY_DIR}/language_0.cpp)

include_directories(".")

add_executable(frontend
	frontend.cpp
	${FLEX_flexThing_OUTPUTS}

	token.hpp
)
