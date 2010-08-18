cmake_minimum_required (VERSION 2.6) 
project (dirwalk)

set (dirwalk_VERSION_MAJOR 0)
set (dirwalk_VERSION_MINOR 0)
set (dirwalk_VERSION_PATCH 1)

add_subdirectory(src)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(UseDoxygen)

find_package(Boost 1.41 COMPONENTS system filesystem)

if(Boost_FOUND)
	link_directories(${Boost_LIBRARY_DIRS})
	include_directories(${Boost_INCLUDE_DIRS})
endif()
