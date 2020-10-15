cmake_minimum_required(VERSION 3.14)

project(
    LinkedList
    LANGUAGES C CXX
    DESCRIPTION "A singly Linked List implementation."
)

set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
		set(USE_GCOV ON)
		set(Python_FIND_STRATEGY LOCATION)
		find_package(Python COMPONENTS Interpreter)
		if(Python_Interpreter_FOUND)
			set(PYTHON_EXECUTABLE ${Python_EXECUTABLE})
		endif()
		include( cmake/CodeCoverage.cmake )
		SET(GCC_COVERAGE_COMPILE_FLAGS "-g -O0 --coverage -fprofile-arcs -ftest-coverage")
		SET(GCC_COVERAGE_LINK_FLAGS    "-lgcov")
		SET(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
		SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
		SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")


		SETUP_TARGET_FOR_COVERAGE_COBERTURA( GenerateCoverage ctest Coverage )
	endif()
endif()

# Main Library
add_library(LinkedList lib/linked_list.c)
target_include_directories(LinkedList PUBLIC lib)


if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	if(BUILD_EXAMPLE)
		add_subdirectory(examples)
	endif()
	if(BUILD_TESTING)
		include(CTest)
		# ========================================================= 
		# Download and unpack googletest at configure time
		configure_file(cmake/GTestCMakeLists.txt.in googletest-download/CMakeLists.txt)
		execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
		RESULT_VARIABLE result
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
		if(result)
		message(FATAL_ERROR "CMake step for googletest failed: ${result}")
		endif()
		execute_process(COMMAND ${CMAKE_COMMAND} --build .
		RESULT_VARIABLE result
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
		if(result)
		message(FATAL_ERROR "Build step for googletest failed: ${result}")
		endif()

		# Prevent overriding the parent project's compiler/linker
		# settings on Windows
		set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

		# Add googletest directly to our build. This defines
		# the gtest and gtest_main targets.
		add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
						${CMAKE_CURRENT_BINARY_DIR}/googletest-build
						EXCLUDE_FROM_ALL)

		# The gtest/gtest_main targets carry header search path
		# dependencies automatically when using CMake 2.8.11 or
		# later. Otherwise we have to add them here ourselves.
		if (CMAKE_VERSION VERSION_LESS 2.8.11)
		include_directories("${gtest_SOURCE_DIR}/include")
		endif()
		# ========================================================= 
		add_subdirectory(tests)
	endif()
endif()


