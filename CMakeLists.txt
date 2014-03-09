cmake_minimum_required(VERSION 2.0)

project(HellmanCompiler CXX)

find_package(CXXFeatures)

set(needed_features
	CXXFeatures_nullptr
)
foreach(feature ${needed_features})
	if(NOT ${feature}_FOUND)
		message(FATAL_ERROR "CXX feature \"${feature}\" is not supported by the compiler.")
	endif()
endforeach()

find_package(FLEX)
FLEX_TARGET(flexThing language_0.lex ${CMAKE_CURRENT_BINARY_DIR}/language_0.cpp)

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
