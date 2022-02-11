cmake_minimum_required(VERSION 3.15)
project(Base64 VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(GTest CONFIG REQUIRED)

file(GLOB_RECURSE src *.cpp *.hpp *.c *.h *.cc)

add_executable(TestsBase64 ${src})

if (MSVC)
      set_property(TARGET TestsBase64 PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")  
else()
endif()

target_include_directories(TestsBase64 PUBLIC ${INCLUDES} include)
target_link_libraries(TestsBase64 PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)

add_test(
        NAME TestsBase64
        COMMAND TestsBase64
)