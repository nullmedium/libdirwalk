cmake_minimum_required (VERSION 2.6) 
project (dirwalk)

set (dirwalk_VERSION_MAJOR 0)
set (dirwalk_VERSION_MINOR 0)
set (dirwalk_VERSION_PATCH 1)

find_package(Boost 1.42.0 COMPONENTS system filesystem)
link_directories(${Boost_LIBRARY_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

install (FILES dirwalker.h DESTINATION include)
