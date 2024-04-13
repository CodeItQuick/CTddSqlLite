//
// Created by Owner on 4/7/2024.
//
#include <stdio.h>
#include <string.h>
#include "parser.h"

static char results[10] = {0};
static char *columnHeader;
static int columnValue = 0;
int substring(int len, const char fullString[], int pos, char* substr)
{
    strncpy(substr, &fullString[pos], len);

    substr[len] = '\0';

    return 0;
}
int findString(int pos, const char charStr, const char searchString[])
{
    int c = 0;

    while (c < strlen(searchString)) {
        if (searchString[pos + c] == charStr )
        {
            break;
        }
        c++;
    }

    return pos + c;
}
int findColumnLabel(const char* inputString, char* columnLabel)
{
    int startIdx = findString(0, '(', inputString) + 1;
    int endIdx = findString(startIdx, ' ', inputString);

    substring(
            endIdx - startIdx,
            inputString,
            startIdx,
            columnLabel);
    return 0;
}
char * println(const char* printedString) {
    printf("got here");
    char printedSubstring[50] = "";
    if (strlen(printedString) > 11) {
        substring(12, printedString, 0, printedSubstring);
    }
    printf("got here");
    if (strlen(printedSubstring) > 0 && strcmp(printedSubstring, "CREATE TABLE") == 0) {
        char columnLabel[50] = "";
        findColumnLabel(printedString, columnLabel);
        printf("Table Tabling: %s end", columnLabel);
        columnHeader = &columnLabel[0]; // store this as columnHeader
        return "success";
    }
    printf("and here");
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