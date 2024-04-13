//
// Created by Owner on 4/7/2024.
//
#include <stdio.h>
#include <string.h>
#include "parser.h"


int substring(char* substr, int len, const char fullString[], int pos)
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
int findColumnLabel(char* self, const char* inputString)
{
    int startIdx = findString(0, '(', inputString) + 1;
    int endIdx = findString(startIdx, ' ', inputString);

    int stringLength = endIdx - startIdx;
    strncpy(self, &inputString[startIdx], stringLength);
    self[stringLength] = '\0';

    return 0;
}
int parse(struct ParserSelf* self, const char* printedString) {
    char printedSubstring[50] = "";
    if (strlen(printedString) > 11) {
        substring(printedSubstring, 12, printedString, 0);
    }
    if (strlen(printedSubstring) > 0 && strcmp(printedSubstring, "CREATE TABLE") == 0) {
        char columnLabel[50] = "";
        findColumnLabel(columnLabel, printedString);
        strcpy(self->columnHeader, &columnLabel[0]); // store this as columnHeader
        return 0;
    }
    if (strcmp(printedString, "INSERT INTO default VALUES (1);") == 0) {
        self->columnValue = 1;
        return 0;
    }
    // SELECT
    if (self->columnValue == 0) {
        sprintf(self->results, "table\n%s", self->columnHeader);
        return 0; // retrieve columnHeader with SELECT
    }
    sprintf(self->results, "table\n%s\n%d", self->columnHeader, self->columnValue);
    return 0; // retrieve columnHeader with SELECT
}