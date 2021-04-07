cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)

##########################################################

find_package(Boost COMPONENTS program_options REQUIRED)
if(NOT Boost_FOUND)
	message(SEND_ERROR "Failed to find boost::program_options")
	return()
else()
	include_directories(${Boost_INCLUDE_DIRS})
endif()

##########################################################

add_executable(main main.cpp)
target_link_libraries(main ${Boost_LIBRARIES})
