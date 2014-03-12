cmake_minimum_required(VERSION 2.0)

project(HellmanCompiler CXX)

# TODO: Error checking.
find_package(FLEX)
FLEX_TARGET(flexScanner language_0.l ${CMAKE_CURRENT_BINARY_DIR}/language_0.cpp)

# TODO: Organize files.
include_directories(
	"."
	${FLEX_INCLUDE_DIR}
)

if(MSVC)
	# Why /SAFESEH?
		# If the version used to build a library (like fl) doesn't match the one you're
		# using, this setting will error during linking. Turning it off here lets
		# us use VS2013 with whichever version of Flex we got.

	set(CMAKE_EXE_LINKER_FLAGS
		"${CMAKE_EXE_LINKER_FLAGS} /SAFESEH:NO"
	)
	add_definitions(
		# Listen to warnings! They're there for a reason.
		# Anything higher will start checking the standard headers. Yes, really.
		/W4
	)
else()
	add_definitions(
		-std=c++11
		# Listen to warnings! They're there for a reason.
		-Wall -Wextra
	)
endif()

add_executable(frontend
	token.hpp
	token.cpp

	frontend.cpp

	${FLEX_flexScanner_OUTPUTS}
)
target_link_libraries(frontend fl)
