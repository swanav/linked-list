cmake_minimum_required(VERSION 3.14)

project(
    LinkedList
    LANGUAGES C
    DESCRIPTION "A singly Linked List implementation."
)

set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)

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
