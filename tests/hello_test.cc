#include <gtest/gtest.h>
#include "hello_test.h"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
    // Can print hello world
    char helloWorld[] = "hello world";
    char* expect = println(helloWorld);
    EXPECT_STREQ("hello world", expect);
}