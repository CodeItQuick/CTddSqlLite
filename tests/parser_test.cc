#include <gtest/gtest.h>
#include "parser_test.h"
#include <string>

TEST(StatementTokenAssertions, CanRetrieveColumnLabel) {
    char createTableStatement[] = "CREATE TABLE default (Age int);";

    char columnLabel[1][50] = { "" };
    statementTokenValues(columnLabel, createTableStatement, 1);

    EXPECT_STREQ("Age", columnLabel[0]);
}
TEST(StatementTokenAssertions, CanRetrieveColumnLabelId) {
    char createTableStatement[] = "CREATE TABLE default (ID int);";

    char columnLabel[1][50] = { "" };
    statementTokenValues(columnLabel, createTableStatement, 1);

    EXPECT_STREQ("ID", columnLabel[0]);
}
TEST(StatementTokenAssertions, CanRetrieveColumnLabelIdAndLabelAge) {
    char createTableStatement[] = "CREATE TABLE default (ID int,Age int);";

    char columnLabel[2][50] = { "", "" };
    statementTokenValues(columnLabel, createTableStatement, 2);

    EXPECT_STREQ("ID", columnLabel[0]);
    EXPECT_STREQ("Age", columnLabel[1]);
}
TEST(ParseAssertions, CreateTableWithId) {
    char createTableStatement[] = "CREATE TABLE default (ID int);";

    char columnHeader[10][50] = {
            "", "", "", "", "",
            "", "", "", "", ""
            };
    struct ParserSelf self = { "",
                               columnHeader[0], columnHeader[1], columnHeader[2],
                               columnHeader[3], columnHeader[4], columnHeader[5],
                               columnHeader[6], columnHeader[7], columnHeader[8],
                               columnHeader[9] };
    int expect = parse(&self, createTableStatement);

    EXPECT_EQ(0, expect);
}
TEST(ParseAssertions,CreateTableWithAge) {
    char createTableStatement[] = "CREATE TABLE default (Age int);";
    char columnHeader[10][50] = {
            "", "", "", "", "",
            "", "", "", "", ""
            };
    struct ParserSelf self = { "",
                               columnHeader[0], columnHeader[1], columnHeader[2],
                               columnHeader[3], columnHeader[4], columnHeader[5],
                               columnHeader[6], columnHeader[7], columnHeader[8],
                               columnHeader[9] };
    int expect = parse(&self, createTableStatement);

    EXPECT_EQ(0, expect);
}
TEST(ParseAssertions,SelectRetrievesColumnLabel) {
    char createTableStatement[] = "CREATE TABLE default (ID int);";
    char columnHeader[10][50] = {
            "", "", "", "", "",
            "", "", "", "", ""
    };
    struct ParserSelf self = { "",
            columnHeader[0], columnHeader[1], columnHeader[2],
            columnHeader[3], columnHeader[4], columnHeader[5],
            columnHeader[6], columnHeader[7], columnHeader[8],
            columnHeader[9] };
    parse(&self, createTableStatement);
    char select[] = "SELECT * FROM default;";

    parse(&self, select);

    EXPECT_STREQ("table\nID", self.results);
}
TEST(ParseAssertions,SelectRetrievesTwoColumnLabel) {
    char createTableStatement[] = "CREATE TABLE default (ID int,Username varchar);";

    char columnHeader[10][50] = {
            "", "", "", "", "",
            "", "", "", "", ""
            };
    struct ParserSelf self = { "",
                               columnHeader[0], columnHeader[1], columnHeader[2],
                               columnHeader[3], columnHeader[4], columnHeader[5],
                               columnHeader[6], columnHeader[7], columnHeader[8],
                               columnHeader[9] };
    parse(&self, createTableStatement);
    char select[] = "SELECT * FROM default;";

    parse(&self, select);

    EXPECT_STREQ("table\nID\tUsername", self.results);
}
TEST(ParseAssertions,SelectRetrievesThreeColumnLabel) {
    char createTableStatement[] = "CREATE TABLE default (ID int,Username varchar,Age int);";

    char columnHeader[10][50] = {
            "", "", "", "", "",
            "", "", "", "", ""
            };
    struct ParserSelf self = { "",
                               columnHeader[0], columnHeader[1], columnHeader[2],
                               columnHeader[3], columnHeader[4], columnHeader[5],
                               columnHeader[6], columnHeader[7], columnHeader[8],
                               columnHeader[9] };
    parse(&self, createTableStatement);
    char select[] = "SELECT * FROM default;";

    parse(&self, select);

    EXPECT_STREQ("table\nID\tUsername\tAge", self.results);
}
// TODO: next behaviour, add SELECT ID FROM default;
//TEST(ParseAssertions,SelectRetrievesSelectedColumnLabel) {
//    char createTableStatement[] = "CREATE TABLE default (ID int,Username varchar,Age int);";
//
//    char columnHeader[10][50] = {
//            "", "", "", "", "",
//            "", "", "", "", ""
//            };
//    struct ParserSelf self = { "",
//                               columnHeader[0], columnHeader[1], columnHeader[2],
//                               columnHeader[3], columnHeader[4], columnHeader[5],
//                               columnHeader[6], columnHeader[7], columnHeader[8],
//                               columnHeader[9] };
//    parse(&self, createTableStatement);
//    char select[] = "SELECT ID FROM default;";
//
//    parse(&self, select);
//
//    EXPECT_STREQ("table\nID", self.results);
//}
TEST(ParseAssertions,InsertIntoStoresData) {
    char createTable[] = "CREATE TABLE default (ID int);";
    char columnHeader[10][50] = {
            "", "", "", "", "",
            "", "", "", "", ""
    };
    struct ParserSelf self = { "",
                               columnHeader[0], columnHeader[1], columnHeader[2],
                               columnHeader[3], columnHeader[4], columnHeader[5],
                               columnHeader[6], columnHeader[7], columnHeader[8],
                               columnHeader[9] };
    parse(&self, createTable);
    char insertInto[] = "INSERT INTO default VALUES (1);";
    parse(&self, insertInto);
    char select[] = "SELECT * FROM default;";

    parse(&self, select);

    EXPECT_STREQ("table\nID\n1", self.results);
}
TEST(ParseAssertions,InsertIntoStoresAnyNumberData) {
    char createTable[] = "CREATE TABLE default (ID int);";
    char columnHeader[10][50] = {
            "", "", "", "", "",
            "", "", "", "", ""
    };
    struct ParserSelf self = { "",
                               columnHeader[0], columnHeader[1], columnHeader[2],
                               columnHeader[3], columnHeader[4], columnHeader[5],
                               columnHeader[6], columnHeader[7], columnHeader[8],
                               columnHeader[9] };
    parse(&self, createTable);
    char insertInto[] = "INSERT INTO default VALUES (7);";
    parse(&self, insertInto);
    char select[] = "SELECT * FROM default;";

    parse(&self, select);

    EXPECT_STREQ("table\nID\n7", self.results);
}
TEST(ParseAssertions,InsertIntoStoresAddsTwoValues) {
    char createTable[] = "CREATE TABLE default (ID int,Age int);";
    char columnHeader[10][50] = {
            "", "", "", "", "",
            "", "", "", "", ""
    };
    struct ParserSelf self = { "",
                               columnHeader[0], columnHeader[1], columnHeader[2],
                               columnHeader[3], columnHeader[4], columnHeader[5],
                               columnHeader[6], columnHeader[7], columnHeader[8],
                               columnHeader[9] };
    parse(&self, createTable);
    char insertInto[] = "INSERT INTO default VALUES (7,5);";
    parse(&self, insertInto);
    char select[] = "SELECT * FROM default;";

    parse(&self, select);

    EXPECT_STREQ("table\nID\tAge\n7\t5", self.results);
}