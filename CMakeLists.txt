cmake_minimum_required(VERSION 3.14)
project(CTddSqlLite)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_library(
        parser
        src/parser.c
        src/parser.h
)
add_library(
        repl
        src/repl.c
        src/repl.h
)
add_executable(
        main
        src/main.c
)
add_executable(
        parser_test
        tests/parser_test.cc
)
target_link_libraries(
        main
        parser
)
target_link_libraries(
        parser_test
        parser
        GTest::gtest_main
)

add_executable(
        repl_test
        tests/repl_test.cc
)
target_link_libraries(
        repl_test
        repl
        GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(parser_test)
gtest_discover_tests(repl_test)