cmake_minimum_required(VERSION 3.0)
project (hello)

set(CMAKE_BUILD_TYPE Release)

file(GLOB hello_SRC 
	"hello.c"
	)

file(GLOB sendpackets_SRC
	"sendpackets.c"
	)

file(GLOB receivepackets_SRC
	"receivepackets.c"
	)

file (GLOB hello_LIB
	"hellolibfile.c"
	)

file (GLOB semaphore_SRC
	"sem.cpp"
	)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")

add_executable(hello ${hello_SRC})
add_executable(sendpackets ${sendpackets_SRC})
add_executable(receivepackets ${receivepackets_SRC})
add_executable(sem ${semaphore_SRC})
add_library(hellolib ${hello_LIB})
target_link_libraries(hello rt hellolib)
target_link_libraries(sem pthread rt)
