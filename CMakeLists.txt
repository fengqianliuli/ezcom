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
add_executable(sync_example example/sync_example.cpp)
add_executable(async_example example/async_example.cpp)
add_executable(request_forgot_example example/request_forgot_example.cpp)
target_link_libraries(sync_example ezcom)
target_link_libraries(async_example ezcom)
target_link_libraries(request_forgot_example ezcom)

# install ezcom library and simple binary
set(CMAKE_INSTALL_PREFIX install)
install(TARGETS ezcom DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)
install(TARGETS sync_example DESTINATION bin)
install(TARGETS async_example DESTINATION bin)
install(TARGETS request_forgot_example DESTINATION bin)
