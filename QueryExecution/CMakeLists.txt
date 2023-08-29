cmake_minimum_required(VERSION 3.8)
project(CS539_Project)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(src)

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -O3 ")

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(seq-scan-test test/seq_scan_test.cpp)
target_link_libraries(seq-scan-test EXECUTOR)

add_executable(filter-seq-scan-test test/filter_seq_scan_test.cpp)
target_link_libraries(filter-seq-scan-test EXECUTOR)

add_executable(nested-loop-join-test test/nested_loop_join_test.cpp)
target_link_libraries(nested-loop-join-test EXECUTOR)

add_executable(hash-join-test test/hash_join_test.cpp)
target_link_libraries(hash-join-test EXECUTOR)

add_executable(complex-test test/complex_executor_test.cpp)
target_link_libraries(complex-test EXECUTOR)
