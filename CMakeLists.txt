cmake_minimum_required(VERSION 3.20)
project(PC2_InsertOrErase LANGUAGES CXX)

include(CTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(pc2_headers INTERFACE)
target_include_directories(pc2_headers INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_features(pc2_headers INTERFACE cxx_std_17)

add_executable(pc2_main src/main.cpp)
target_link_libraries(pc2_main PRIVATE pc2_headers)

add_executable(pc2_tests tests/test_samples.cpp)
target_link_libraries(pc2_tests PRIVATE pc2_headers)

add_test(NAME pc2_samples COMMAND pc2_tests)