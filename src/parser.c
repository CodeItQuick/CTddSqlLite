//
// Created by Owner on 4/7/2024.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"
// valid statements for parser
char CREATE_STATEMENT[7] = "CREATE";
char INSERT_STATEMENT[7] = "INSERT";
char SELECT_STATEMENT[7] = "SELECT";


int parse(struct ParserSelf* self, const char* statementRequest) {
    struct StatementTokens token = {
            "",
            {
                "","", "", "", "",
                "","", "", "", ""
            }
    };

    Tokenize(statementRequest, &token);

    // CREATE TABLE
    if (strlen(token.command) > 0 && strcmp(token.command, CREATE_STATEMENT) == 0) {
        self->numEntries = numTableColumns(statementRequest);
        statementTokenValues(token.tokens, statementRequest, self->numEntries);
        // loop to determine number of commas/entries in CREATE TABLE statement
        executeCreateTableStatement(self, &token); // TODO: max of 10 columns, produce error message if more attempted
        return 0;
    }
    // INSERT INTO
    if (strlen(token.command) > 0 && strcmp(token.command, INSERT_STATEMENT) == 0) {
        statementTokenValues(token.tokens, statementRequest, self->numEntries);
        executeInsertStatement(self, &token);
        return 0;
    }
    // SELECT
    if (strlen(token.command) > 0 && strcmp(token.command, SELECT_STATEMENT) == 0) {
        // TODO: all SELECT statements are SELECT *, add statements into it
        // statementTokenValues(token.tokens, statementRequest, self->numEntries);
        sprintf(self->results, "table\n");
        // row headers
        executeSelectTableHeaders(self);
        executeSelectTableValues(self);
        return 0; // retrieve columnHeader with SELECT
    }
    return 1; // error, should have attempted at least one valid statement
}
void
Tokenize(const char *statementRequest, struct StatementTokens *token) {
    if (strlen(statementRequest) > 6) {
        strncpy(token->command, &statementRequest[0], 6);
        token->command[6] = '\0';
    }
}
// String Helper Functions
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
int statementTokenValues(char self[][50], const char* inputString, int selfArraySize)
{
    int startIdx = findString(0, '(', inputString) + 1;
    int endIdx = findString(startIdx, ' ', inputString);

    int stringLength = endIdx - startIdx;
    strncpy(self[0], &inputString[startIdx], stringLength);

    for (int i = 1; i < selfArraySize; i++) {
        int commaIdx = findString(startIdx, ',', inputString) + 1;
        int commaSpaceIdx = findString(commaIdx, ' ', inputString);
        strncpy(self[i], &inputString[commaIdx], commaSpaceIdx - commaIdx);
        self[i][commaSpaceIdx - commaIdx + 1] = '\0';
        startIdx = commaIdx;
    }

    return 0;
}
// String Helper Functions
void executeCreateTableStatement(const struct ParserSelf *self, struct StatementTokens *token) {
    for (int i = 0; i < self->numEntries; i++) {
        strncpy(self->columnHeaders[i], &token->tokens[i][0], strlen(token->tokens[i])); // store this as columnHeader
    }
}
void executeInsertStatement(struct ParserSelf *self, struct StatementTokens *token) {
    for (int i = 0; i < self->numEntries; i++) {
        self->columnValues[i] = atoi(token->tokens[i]);
    }
}
void executeSelectTableValues(struct ParserSelf *self) {// goto next line if row values exist
    if (self->columnValues[0] != 0) {
        strcat(self->results, "\n");
    }
    // print row values
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
}

void executeSelectTableHeaders(struct ParserSelf *self) {
    for(int i = 0; i < self->numEntries; i++) {
        char* currentRow = self->columnHeaders[i];
        // do not add \t to last entry
        if (i < self->numEntries - 1) {
            strcat(currentRow, "\t");
        }
        strcat(self->results, currentRow);
    }
}

int numTableColumns(const char *printedString) {
    int startIdx = 0, commaIdx = 0, numEntries = 0;
    while(startIdx < strlen(printedString)) {
        startIdx = findString(commaIdx + 1, ',', printedString);
        commaIdx = startIdx;
        numEntries++;
    }
    return numEntries;
}
