cmake_minimum_required(VERSION 3.10)

project(ezcom VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set("${CMAKE_CXX_FLAGS} -Wall -Werror")

file(GLOB_RECURSE EZCOM_SOURCES "src/*.cpp" "proto/*.cc")

add_library(ezcom SHARED ${EZCOM_SOURCES})

target_include_directories(ezcom PUBLIC ${CMAKE_SOURCE_DIR}
                                        ${CMAKE_SOURCE_DIR}/include
                                        /usr/local/include)
target_link_directories(ezcom PUBLIC /usr/local/lib)
target_link_libraries(ezcom PUBLIC libprotobuf.a zmq pthread)

# build simple example
add_executable(simple example/simple.cpp)
target_link_libraries(simple ezcom)

# install ezcom library and simple binary
set(CMAKE_INSTALL_PREFIX install)
install(TARGETS ezcom DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)
install(TARGETS simple DESTINATION bin)
