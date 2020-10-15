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
		list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)
		set(Python_FIND_STRATEGY LOCATION)
		find_package(Python COMPONENTS Interpreter)
		if(Python_Interpreter_FOUND)
			set(PYTHON_EXECUTABLE ${Python_EXECUTABLE})
		endif()
		include( cmake_modules/CodeCoverage.cmake )
		SET(GCC_COVERAGE_COMPILE_FLAGS "-g -O0 --coverage -fprofile-arcs -ftest-coverage")
		SET(GCC_COVERAGE_LINK_FLAGS    "-lgcov")
		SET(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
		SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
		SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

		SETUP_TARGET_FOR_COVERAGE( HtmlCoverage ctest HtmlCoverage )
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
		add_subdirectory(tests)
	endif()
endif()


