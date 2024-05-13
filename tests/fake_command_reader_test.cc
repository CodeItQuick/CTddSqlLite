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

    char columnHeader[10][10] = {
            "", "", "", "", "",
            "", "", "", "", ""
    };
    struct ParserSelf self = { "",
                               columnHeader[0], columnHeader[1], columnHeader[2],
                               columnHeader[3], columnHeader[4], columnHeader[5],
                               columnHeader[6], columnHeader[7], columnHeader[8],
                               columnHeader[9] };
    struct replCommands commands = {
            "CREATE TABLE default (ID int);",
            "",
            "",
            "",
            "",
    };

    executeCommand(&commands, &self);

    EXPECT_STREQ("success\n", self.results);
}
TEST(ReplTests, CanExecuteTwoInputs) {

    char columnHeader[10][10] = {
            "", "", "", "", "",
            "", "", "", "", ""
    };
    struct ParserSelf self = { "",
                               columnHeader[0], columnHeader[1], columnHeader[2],
                               columnHeader[3], columnHeader[4], columnHeader[5],
                               columnHeader[6], columnHeader[7], columnHeader[8],
                               columnHeader[9] };
    struct replCommands commands = {
            "CREATE TABLE default (ID int);",
            "SELECT * FROM default;",
            "",
            "",
            "",
    };

    executeCommand(&commands, &self);

    EXPECT_STREQ("success\ntable\nID\n", self.results);
}
TEST(ReplTests, CanExecuteFiveInputs) {

    char columnHeader[10][10] = {
            "", "", "", "", "",
            "", "", "", "", ""
    };
    struct ParserSelf self = { "",
                               columnHeader[0], columnHeader[1], columnHeader[2],
                               columnHeader[3], columnHeader[4], columnHeader[5],
                               columnHeader[6], columnHeader[7], columnHeader[8],
                               columnHeader[9] };
    struct replCommands commands = {
            "CREATE TABLE default (ID int);",
            "SELECT * FROM default;",
            "SELECT * FROM default;",
            "SELECT * FROM default;",
            "SELECT * FROM default;",
    };

    executeCommand(&commands, &self);

    EXPECT_STREQ("success\ntable\nID\ntable\nID\ntable\nID\ntable\nID\n", self.results);
}