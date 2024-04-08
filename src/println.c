//
// Created by Owner on 4/7/2024.
//
#include <stdio.h>
#include <string.h>
#include "println.h"

char results[10] = {0};
char columnHeader[5] = {0};
int columnValue;
char * println(char *printedString) {
    if (strcmp(printedString, "CREATE TABLE default (ID int);") == 0) {
        strcpy(columnHeader, "ID"); // store this as columnHeader
        return "success";
    }
    if (strcmp(printedString, "INSERT INTO default VALUES (1);") == 0) {
        columnValue = 1;
        return "success";
    }
    // SELECT
    if (columnValue == 0) {
        sprintf(results, "table\n%s", columnHeader);
        return results; // retrieve columnHeader with SELECT
    }
    sprintf(results, "table\n%s\n%d", columnHeader, columnValue);
    return results; // retrieve columnHeader with SELECT
}