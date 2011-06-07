cmake_minimum_required (VERSION 2.6) 

include_directories("../src")

add_executable(dirwalker dirwalker.cpp)
target_link_libraries(dirwalker ${Boost_LIBRARIES}) 

add_executable(fgrep fgrep.cpp)
target_link_libraries(fgrep ${Boost_LIBRARIES}) 
