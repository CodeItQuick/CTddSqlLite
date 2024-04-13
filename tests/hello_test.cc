#include <gtest/gtest.h>
#include "hello_test.h"
#include <string>

TEST(CreateTableWithId, BasicAssertions) {
    std::string createTableStatement = "CREATE TABLE default (ID int);";
    struct ParserSelf self = { "", "", 0 };
    int expect = parse(&self, createTableStatement.c_str());

    EXPECT_EQ(0, expect);
}
TEST(CanRetrieveColumnLabel, BasicAssertions) {
    std::string createTableStatement = "CREATE TABLE default (Age int);";

    char columnLabel[50] = "";
    findColumnLabel(columnLabel, createTableStatement.c_str());

    EXPECT_STREQ("Age", columnLabel);
}
TEST(CanRetrieveColumnLabelId, BasicAssertions) {
    std::string createTableStatement = "CREATE TABLE default (ID int);";

    char columnLabel[50] = "";
    findColumnLabel(columnLabel, createTableStatement.c_str());

    EXPECT_STREQ("ID", columnLabel);
}
// Not ready for age yet
TEST(CreateTableWithAge, BasicAssertions) {
    char helloWorld[] = "CREATE TABLE default (Age int);";
    struct ParserSelf self = { "", "", 0 };
    int expect = parse(&self, helloWorld);

    EXPECT_EQ(0, expect);
}
TEST(SelectRetrievesColumnLabel, BasicAssertions) {
    char createTable[] = "CREATE TABLE default (ID int);";
    struct ParserSelf self = { "", "", 0 };
    parse(&self, createTable);
    char select[] = "SELECT * FROM default;";

    parse(&self, select);

    EXPECT_STREQ("table\nID", self.results);
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