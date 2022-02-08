cmake_minimum_required(VERSION 3.15)
project(Base64 VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE src *.cpp *.hpp *.c *.h *.cc)
add_executable(Base64 ${src})

target_include_directories(Base64 PUBLIC ${INCLUDES} include)