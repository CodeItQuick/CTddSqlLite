#include <gtest/gtest.h>
#include "hello_test.h"
#include <string>

TEST(CreateTableWithId, BasicAssertions) {
    std::string createTableStatement = "CREATE TABLE default (ID int);";

    char* expect = println(createTableStatement.c_str());

    EXPECT_STREQ("success", expect);
}
TEST(CanRetrieveColumnLabel, BasicAssertions) {
    std::string createTableStatement = "CREATE TABLE default (Age int);";

    char columnLabel[50] = "";
    findColumnLabel(createTableStatement.c_str(), columnLabel);

    EXPECT_STREQ("Age", columnLabel);
}
TEST(CanRetrieveColumnLabelId, BasicAssertions) {
    std::string createTableStatement = "CREATE TABLE default (ID int);";

    char columnLabel[50] = "";
    findColumnLabel(createTableStatement.c_str(), columnLabel);

    EXPECT_STREQ("ID", columnLabel);
}
// Not ready for age yet
TEST(CreateTableWithAge, BasicAssertions) {
    char helloWorld[] = "CREATE TABLE default (Age int);";

    char* expect = println(helloWorld);

    EXPECT_STREQ("success", expect);
}
TEST(SelectRetrievesColumnLabel, BasicAssertions) {
    char createTable[] = "CREATE TABLE default (ID int);";
    println(createTable);
    char select[] = "SELECT * FROM default;";

    char* expect = println(select);

    EXPECT_STREQ("table\nID", expect);
}
TEST(InsertIntoStoresData, BasicAssertions) {
    char createTable[] = "CREATE TABLE default (ID int);";
    println(createTable);
    char insertInto[] = "INSERT INTO default VALUES (1);";
    println(insertInto);
    char select[] = "SELECT * FROM default;";

    char* expect = println(select);

    EXPECT_STREQ("table\nID\n1", expect);
}