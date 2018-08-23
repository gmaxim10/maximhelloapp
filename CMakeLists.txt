cmake_minimum_required(VERSION 3.0)
project (hello)

set(CMAKE_BUILD_TYPE Release)

file(GLOB hello_SRC 
	"hello.c"
	)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")

add_executable(hello ${hello_SRC})
target_link_libraries(hello rt)
