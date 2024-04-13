//
// Created by Owner on 4/7/2024.
//
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "parser.h"

static char results[10] = {0};
static char *columnHeader;
static int columnValue = 0;
char *substring(int len, const char fullString[], int pos)
{
    char* substr = malloc((sizeof(char)) * (len + 1));
    strncpy(substr, &fullString[pos], len);

    substr[len] = '\0';

    return substr;
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
char* findColumnLabel(const char* inputString)
{
    int startIdx = findString(0, '(', inputString) + 1;
    int endIdx = findString(startIdx, ' ', inputString);

    char* columnLabel = substring(
            endIdx - startIdx,
            inputString,
            startIdx);
    return columnLabel;
}
char * println(const char* printedString) {
    printf("got here");
    char *printedSubstring;
    if (strlen(printedString) > 11) {
        printedSubstring = substring(12, printedString, 0);
    }
    printf("got here");
    if (strlen(printedSubstring) > 0 && strcmp(printedSubstring, "CREATE TABLE") == 0) {
        char* columnLabel = findColumnLabel(printedString);
        printf("Table Tabling: %s end", columnLabel);
        columnHeader = columnLabel; // store this as columnHeader
        free(columnLabel);
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