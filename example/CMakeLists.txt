cmake_minimum_required (VERSION 2.6) 
project (dirwalker)

include_directories("..")

find_package(Boost 1.42.0 COMPONENTS system filesystem)
link_directories(${Boost_LIBRARY_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

add_executable(dirwalker main.cpp)
target_link_libraries(dirwalker ${Boost_LIBRARIES}) 
 