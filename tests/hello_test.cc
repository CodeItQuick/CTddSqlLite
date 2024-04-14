#include <gtest/gtest.h>
#include "hello_test.h"
#include <string>

TEST(CreateTableWithId, BasicAssertions) {
    char createTableStatement[] = "CREATE TABLE default (ID int);";
    struct ParserSelf self = { "", "", 0 };
    int expect = parse(&self, createTableStatement);

    EXPECT_EQ(0, expect);
}
TEST(CanRetrieveColumnLabel, BasicAssertions) {
    char createTableStatement[] = "CREATE TABLE default (Age int);";

    char columnLabel[1][50] = { "" };
    findColumnLabel(columnLabel, createTableStatement, 1);

    EXPECT_STREQ("Age", columnLabel[0]);
}
TEST(CanRetrieveColumnLabelId, BasicAssertions) {
    char createTableStatement[] = "CREATE TABLE default (ID int);";

    char columnLabel[1][50] = { "" };
    findColumnLabel(columnLabel, createTableStatement, 1);

    EXPECT_STREQ("ID", columnLabel[0]);
}
TEST(CanRetrieveColumnLabelIdAndLabelAge, BasicAssertions) {
    char createTableStatement[] = "CREATE TABLE default (ID int,Age int);";

    char columnLabel[2][50] = { "", "" };
    findColumnLabel(columnLabel, createTableStatement, 2);

    EXPECT_STREQ("ID", columnLabel[0]);
    EXPECT_STREQ("Age", columnLabel[1]);
}
TEST(CreateTableWithAge, BasicAssertions) {
    char createTableStatement[] = "CREATE TABLE default (Age int);";
    struct ParserSelf self = { "", "", 0 };
    int expect = parse(&self, createTableStatement);

    EXPECT_EQ(0, expect);
}
TEST(SelectRetrievesColumnLabel, BasicAssertions) {
    char createTableStatement[] = "CREATE TABLE default (ID int);";
    struct ParserSelf self = { "", "", 0 };
    parse(&self, createTableStatement);
    char select[] = "SELECT * FROM default;";

    parse(&self, select);

    EXPECT_STREQ("table\nID\t", self.results);
}
TEST(SelectRetrievesTwoColumnLabel, BasicAssertions) {
    char createTableStatement[] = "CREATE TABLE default (ID int,Username varchar);";
    struct ParserSelf self = { "", "", 0 };
    parse(&self, createTableStatement);
    char select[] = "SELECT * FROM default;";

    parse(&self, select);

    EXPECT_STREQ("table\nID\tUsername", self.results);
}
TEST(SelectRetrievesThreeColumnLabel, BasicAssertions) {
    char createTableStatement[] = "CREATE TABLE default (ID int,Username varchar,Age int);";
    struct ParserSelf self = { "", "", 0 };
    parse(&self, createTableStatement);
    char select[] = "SELECT * FROM default;";

    parse(&self, select);

    EXPECT_STREQ("table\nID\tUsername\tAge", self.results);
}
TEST(InsertIntoStoresData, BasicAssertions) {
    char createTable[] = "CREATE TABLE default (ID int);";
    struct ParserSelf self = { "", "", 0 };
    parse(&self, createTable);
    char insertInto[] = "INSERT INTO default VALUES (1);";
    parse(&self, insertInto);
    char select[] = "SELECT * FROM default;";

    parse(&self, select);

    EXPECT_STREQ("table\nID\n1", self.results);
}