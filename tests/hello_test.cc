#include <gtest/gtest.h>
#include "hello_test.h"

TEST(CreateTableWithId, BasicAssertions) {
    char helloWorld[] = "CREATE TABLE default (ID int);";

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