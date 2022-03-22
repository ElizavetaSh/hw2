cmake_minimum_required(VERSION 3.13)
project(hw2 C)
project(tests CXX)


set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(GCC_COVERAGE_COMPILE_FLAGS "-pthread")

add_compile_options(-Wall -Wextra -Wpedantic)

add_compile_options(-pthread) 
add_link_options(-pthread)


option(WITH_COVERAGE "Add coverage estimation")
option(ADDRESS_SANITIZER "Add address sanitizer")
option(UNDEFINED_SANITIZER "Add undefined sanitizer")
option(THREAD_SANITIZER "Add thread sanitizer")
option(LEAK_SANITIZER "Add leak sanitizer")
option(paral "Parallel calculate")

if(WITH_COVERAGE)
    add_compile_options(--coverage)
    add_link_options(--coverage)
endif()


if(ADDRESS_SANITIZER)
    add_compile_options(-fsanitize=address)
    add_link_options(-fsanitize=address)

elseif(UNDEFINED_SANITIZER)
    add_compile_options(-fsanitize=undefined)
    add_link_options(-fsanitize=undefined)

elseif(THREAD_SANITIZER)
    add_compile_options(-fsanitize=thread)
    add_link_options(-fsanitize=thread)

elseif(LEAK_SANITIZER)
    add_compile_options(-fsanitize=leak)
    add_link_options(-fsanitize=leak)
endif()


add_library(input_lib STATIC scr/input.c)
target_include_directories(input_lib PUBLIC include)

add_library(static_sequence_lib STATIC scr/static_sequence.c)
target_include_directories(static_sequence_lib PUBLIC include)

add_library(paral_sequence_lib SHARED scr/paral_sequence.c)
target_include_directories(paral_sequence_lib PUBLIC include)

find_package(Threads REQUIRED)
add_executable(hw2 scr/main.c)

set(THREADS_PREFER_PTHREAD_FLAG ON)


if(paral)
    target_link_libraries(hw2 input_lib paral_sequence_lib)
else()
    target_link_libraries(hw2 input_lib static_sequence_lib)
endif()



find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


add_executable(test_input tests/test_input.cpp)
target_link_libraries(test_input input_lib ${GTEST_LIBRARIES} pthread)


add_executable(test_stat_seqn tests/test_stat_dim_lib.cpp)
target_link_libraries(test_stat_seqn input_lib static_sequence_lib ${GTEST_LIBRARIES} pthread)


add_executable(test_dim_seqn tests/test_stat_dim_lib.cpp)
target_link_libraries(test_dim_seqn input_lib paral_sequence_lib ${GTEST_LIBRARIES} pthread)

enable_testing()
add_test(NAME test_input
        COMMAND test_input
        WORKING_DIRECTORY ../tests/data_test/)
add_test(NAME test_stat_seqn 
         COMMAND test_stat_seqn 
         WORKING_DIRECTORY ../tests/data_test/)
add_test(NAME test_dim_seqn 
         COMMAND test_dim_seqn 
         WORKING_DIRECTORY ../tests/data_test/)


