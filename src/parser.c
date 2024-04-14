//
// Created by Owner on 4/7/2024.
//
#include <stdio.h>
#include <string.h>
#include "parser.h"

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

int findColumnLabel(char self[][50], const char* inputString, int selfArraySize)
{
    int startIdx = findString(0, '(', inputString) + 1;
    int endIdx = findString(startIdx, ' ', inputString);

    int stringLength = endIdx - startIdx;
    strncpy(self[0], &inputString[startIdx], stringLength);

    if(selfArraySize == 2)
    {
        int commaIdx = findString(startIdx, ',', inputString) + 1;
        int commaSpaceIdx = findString(commaIdx, ' ', inputString);
        strncpy(self[1], &inputString[commaIdx], commaSpaceIdx - commaIdx);
    }

    return 0;
}
int parse(struct ParserSelf* self, const char* printedString) {
    char printedSubstring[50] = "";
    if (strlen(printedString) > 11) {
        strncpy(printedSubstring, &printedString[0], 12);
        printedSubstring[12] = '\0';
    }
    if (strlen(printedSubstring) > 0 && strcmp(printedSubstring, "CREATE TABLE") == 0) {
        int commaIdx = findString(0, ',', printedString);
        if (commaIdx < strlen(printedString)) {
            char columnLabel[2][50] = { "", "" };
            findColumnLabel(columnLabel, printedString, 2);
            strcpy(self->columnHeaders[0], &columnLabel[0][0]); // store this as columnHeader
            strcpy(self->columnHeaders[1], &columnLabel[1][0]); // store this as columnHeader
        } else {
            char columnLabel[1][50] = { "" };
            findColumnLabel(columnLabel, printedString, 1);
            strcpy(self->columnHeaders[0], &columnLabel[0][0]); // store this as columnHeader
            strcpy(self->columnHeaders[1], ""); // store this as columnHeader
        }
        return 0;
    }
    if (strcmp(printedString, "INSERT INTO default VALUES (1);") == 0) {
        self->columnValue = 1;
        return 0;
    }
    // SELECT
    if (self->columnValue == 0) {
        sprintf(self->results, "table\n%s\t%s", self->columnHeaders[0], self->columnHeaders[1]);
        return 0; // retrieve columnHeader with SELECT
    }
    sprintf(self->results, "table\n%s\n%d", self->columnHeaders[0], self->columnValue);
    return 0; // retrieve columnHeader with SELECT
}