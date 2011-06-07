cmake_minimum_required (VERSION 2.6) 
project (libdirwalk)

set (libdirwalk_VERSION_MAJOR 0)
set (libdirwalk_VERSION_MINOR 0)
set (libdirwalk_VERSION_PATCH 1)

find_package(Boost 1.41 COMPONENTS system filesystem)

if(Boost_FOUND)
	link_directories(${Boost_LIBRARY_DIRS})
	include_directories(${Boost_INCLUDE_DIRS})
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(UseDoxygen)

add_subdirectory(src)
add_subdirectory(example)
