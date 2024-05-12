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
        command_reader
        src/command_reader.c
        src/command_reader.h
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
        command_reader
        repl
)
target_link_libraries(
        parser_test
        parser
        GTest::gtest_main
)

add_executable(
        fake_command_reader_test
        tests/fake_command_reader_test.cc
)
add_library(
        fake_command_reader
        tests/fake_command_reader.cc
        tests/fake_command_reader.h
)
target_link_libraries(
        fake_command_reader_test
        fake_command_reader
        repl
        GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(parser_test)
gtest_discover_tests(fake_command_reader_test)