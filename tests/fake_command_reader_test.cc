//
// Created by Owner on 5/11/2024.
//
#include <gtest/gtest.h>
#include "fake_command_reader.cc"
#include "fake_command_reader_test.h"

TEST(CommandTests, CanReceiveInput) {

    struct commands commands = {
"CREATE TABLE default (ID int);",
""
    };

    char *command = commands_reader(commands, 0);

    EXPECT_STREQ("CREATE TABLE default (ID int);", command);
}
TEST(CommandTests, CanReplayTwoInputs) {

    struct commands commands = {
            "CREATE TABLE default (ID int);",
            "SELECT * FROM default;"
    };

    char *commandOne = commands_reader(commands, 0);
    char *commandTwo = commands_reader(commands, 1);

    EXPECT_STREQ("CREATE TABLE default (ID int);", commandOne);
    EXPECT_STREQ("SELECT * FROM default;", commandTwo);
}
TEST(CommandTests, CanReplayThreeInputs) {

    struct commands commands = {
            "CREATE TABLE default (ID int);",
            "SELECT * FROM default;",
            "SELECT * FROM defaultTwo;"
    };

    char *commandOne = commands_reader(commands, 0);
    char *commandTwo = commands_reader(commands, 1);
    char *commandThree = commands_reader(commands, 2);

    EXPECT_STREQ("CREATE TABLE default (ID int);", commandOne);
    EXPECT_STREQ("SELECT * FROM default;", commandTwo);
    EXPECT_STREQ("SELECT * FROM defaultTwo;", commandThree);
}
TEST(ReplTests, CanExecuteAnInput) {

    struct replCommands commands = {
            "CREATE TABLE default (ID int);",
            "",
            "",
            "",
            "",
    };

    int success = repl(commands);

    EXPECT_EQ(0, success);
}