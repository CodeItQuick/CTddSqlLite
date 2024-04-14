//
// Created by Owner on 4/7/2024.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"

int numEntriesInStatement(const char *printedString);

void createColumns(const struct ParserSelf *self, const char *printedString);

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
    // CREATE TABLE
    if (strlen(printedSubstring) > 0 && strcmp(printedSubstring, "CREATE TABLE") == 0) {
        // loop to determine number of commas/entries in CREATE TABLE statement
        self->numEntries = numEntriesInStatement(printedString);

        // TODO: max of 10 columns, produce error message if more attempted
        createColumns(self, printedString);

        return 0;
    }
    // INSERT INTO
    if (strlen(printedSubstring) > 0 && strcmp(printedSubstring, "INSERT INTO ") == 0) {
        int startIdx = findString(0, '(', printedString) + 1;
        int endIdx = findString(startIdx, ')', printedString);

        // for single entry in VALUES (7)
        if (self->numEntries == 1) {
            int stringLength = endIdx - startIdx;
            char insertValue[5] = "";
            strncpy(insertValue, &printedString[startIdx], stringLength);
            self->columnValues[0] = atoi(insertValue);
        }
        for (int i = 0; i < self->numEntries; i++) {
            int commaIdx = findString(0, ',', printedString) + 1;
            int startToCommaLength = endIdx - startIdx;
            char insertValue[5] = "";
            strncpy(insertValue, &printedString[startIdx], startToCommaLength);
            self->columnValues[i] = atoi(insertValue);
            startIdx = commaIdx;
        }
        return 0;
    }
    // SELECT
    sprintf(self->results, "table\n");
    for(int i = 0; i < self->numEntries; i++) {
        char* currentRow = self->columnHeaders[i];
        // do not add \t to last entry
        if (i < self->numEntries - 1) {
            strcat(currentRow, "\t");
        }
        strcat(self->results, currentRow);
    }
    if (self->columnValues[0] != 0) {
        strcat(self->results, "\n");
    }
    for (int i = 0; i < self->numEntries; i++) {
        if (self->columnValues[i] != 0) {
            char currentRowValues[10] = "";
            sprintf(currentRowValues, "%d", self->columnValues[i]);
            // do not add \t to last entry
            if (i < self->numEntries - 1) {
                strcat(currentRowValues, "\t");
            }
            strcat(self->results, currentRowValues);
        }
    }
//    if (self->columnValues[0] != 0) {
//        char temp[10] = "";
//        sprintf(temp, "\n%d", self->columnValues[0]);
//        strcat(self->results, temp);
//    }
    return 0; // retrieve columnHeader with SELECT
}

int numEntriesInStatement(const char *printedString) {
    int startIdx = 0, commaIdx = 0, numEntries = 0;
    while(startIdx < strlen(printedString)) {
        startIdx = findString(commaIdx + 1, ',', printedString);
        commaIdx = startIdx;
        numEntries++;
    }
    return numEntries;
}

void createColumns(const struct ParserSelf *self, const char *printedString) {
    char temp[10][50] = {"", "", "", "", "", "", "", "", "", "" };
    findColumnLabel(temp, printedString, self->numEntries);
    for (int i = 0; i < self->numEntries; i++) {
        printf("columnLabel: %s", temp[i]);
        strcpy(self->columnHeaders[i], &temp[i][0]); // store this as columnHeader
    }
}
