#include <gtest/gtest.h>
#include "../src/main.c"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
    // Can print hello world
    char helloWorld[] = "Hello, World!\n";
    char *then = println(helloWorld);
    ASSERT_TRUE(strcmp("hello world", then));
}