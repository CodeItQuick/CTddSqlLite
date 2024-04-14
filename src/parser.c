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

    for (int i = 1; i < selfArraySize; i++) {
        int commaIdx = findString(startIdx, ',', inputString) + 1;
        int commaSpaceIdx = findString(commaIdx, ' ', inputString);
        strncpy(self[i], &inputString[commaIdx], commaSpaceIdx - commaIdx);
        startIdx = commaIdx;
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
        // loop to determine number of commas/entries in CREATE TABLE statement
        int startIdx = 0, commaIdx = 0, numEntries = 0;
        while(startIdx < strlen(printedString)) {
            startIdx = findString(commaIdx + 1, ',', printedString);
            commaIdx = startIdx;
            numEntries++;
        }

        // TODO: max of 10 columns, produce error message if more attempted
        char temp[10][50] = { "", "", "", "", "", "", "", "", "", "" };
        findColumnLabel(temp, printedString, numEntries);
        for (int i = 0; i < numEntries; i++) {
            printf("columnLabel: %s", temp[i]);
            strcpy(self->columnHeaders[i], &temp[i][0]); // store this as columnHeader
        }

        return 0;
    }
    if (strcmp(printedString, "INSERT INTO default VALUES (1);") == 0) {
        self->columnValue = 1;
        return 0;
    }
    // SELECT
    if (self->columnValue == 0) {
        if (strlen(self->columnHeaders[2]) > 0) {
            sprintf(self->results, "table\n%s\t%s\t%s", self->columnHeaders[0], self->columnHeaders[1], self->columnHeaders[2]);
        } else {
            sprintf(self->results, "table\n%s\t%s", self->columnHeaders[0], self->columnHeaders[1]);
        }
        return 0; // retrieve columnHeader with SELECT
    }
    sprintf(self->results, "table\n%s\n%d", self->columnHeaders[0], self->columnValue);
    return 0; // retrieve columnHeader with SELECT
}