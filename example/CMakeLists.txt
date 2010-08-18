cmake_minimum_required (VERSION 2.6) 
project (dirwalker)

include_directories("..")

set(Boost_DETAILED_FAILURE_MSG TRUE)
find_package(Boost 1.41.0 COMPONENTS system filesystem)

if (Boost_FOUND)
	link_directories(${Boost_LIBRARY_DIRS})
	include_directories(${Boost_INCLUDE_DIRS})
endif()

add_executable(dirwalker dirwalker.cpp)
target_link_libraries(dirwalker ${Boost_LIBRARIES}) 

add_executable(fgrep fgrep.cpp)
target_link_libraries(fgrep ${Boost_LIBRARIES}) 
