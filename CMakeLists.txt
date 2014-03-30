cmake_minimum_required(VERSION 2.0)

# Do we want to change the name of this?
# I chose it to be a little more descriptive than "Compiler", that's it.
project(HellmanCompiler CXX)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

if(NOT FLEX_FOUND)
	message(FATAL_ERROR "Unable to find flex.")
endif()

if(NOT BISON_FOUND)
	message(FATAL_ERROR "Unable to find Bison.")
endif()

if(WIN32)
	# Flex uses the unistd.h header file, which doesn't exist on Windows.
	# Passing this flag, on a specific port at least, tells Flex to use io.h instead.
	# We need this flag to build on Windows, as far as I can tell.
	# Download Flex and Bison here: http://sourceforge.net/projects/winflexbison/
	set(FLEX_FLAGS "--wincompat")
else()
	set(FLEX_FLAGS "")
endif()

# For convience.
set(BIN ${CMAKE_CURRENT_BINARY_DIR})

FLEX_TARGET(SCANNER language_0.l
	${BIN}/language_0_scanner.cpp COMPILE_FLAGS "${FLEX_FLAGS}")
BISON_TARGET(PARSER language_0.y
	${BIN}/language_0_parser.cpp)
ADD_FLEX_BISON_DEPENDENCY(SCANNER PARSER)

# Disable warnings in auto-generated files. We don't have control over them.
set_source_files_properties(
	${BIN}/language_0_scanner.cpp ${BIN}/language_0_parser.cpp
	PROPERTIES COMPILE_FLAGS /w
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
	include(CheckCXXCompilerFlag)
	CHECK_CXX_COMPILER_FLAG("-std=c++11" CXX11)
	if (CXX11)
		add_definitions("-std=c++11")
	else()
		# Assume it has the older flag. If it doesn't have even that,
		#   we're going to have trouble building anyway.
		add_definitions("-std=c++0x")
	endif()

	add_definitions(
		# Listen to warnings! They're there for a reason.
		-Wall -Wextra
	)
endif()

include_directories(
	${BIN}
)

add_executable(frontend
	frontend.cpp

	${BIN}/language_0_scanner.cpp
	${BIN}/language_0_parser.cpp
)
target_link_libraries(frontend fl)
