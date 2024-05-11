//
// Created by Owner on 5/11/2024.
//
#include <gtest/gtest.h>
#include "command_reader_test.h"

TEST(ReplTests, CanReceiveInput) {

    char *commands[] = {
            "CREATE TABLE default (ID int);"
    };

    char *command = command_reader(commands);

    EXPECT_STREQ("CREATE TABLE default (ID int);", command);
}