//
// Created by Owner on 4/7/2024.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"
// valid statements for parser
const char CREATE_STATEMENT[] = "CREATE";
const char INSERT_STATEMENT[] = "INSERT";
const char SELECT_STATEMENT[] = "SELECT";

int hashFunction(char *token) {
    const char* lookup_table[3] = {
            CREATE_STATEMENT,
            INSERT_STATEMENT,
            SELECT_STATEMENT
    };
    for (int i = 0; i < 3; ++i) {
        if (strcmp(token, lookup_table[i]) == 0) {
            return i;
        }
    }
    return -1;
}

int createTableFunction(struct ParserSelf* self, const char* statementRequest, struct StatementTokens token) {
    self->numTableColumns = numTableColumns(statementRequest);
    statementTokenValues(token.tokens, statementRequest, self->numTableColumns);
    // loop to determine number of commas/entries in CREATE TABLE statement
    executeCreateTableStatement(self,&token); // TODO: max of 10 columns, produce error message if more attempted
    strcpy(self->results, "success\n");
}
int parse(struct ParserSelf* self, const char* statementRequest) {
    struct StatementTokens token = {
            "",
            {
                    "", "", "", "", "",
                    "", "", "", "", ""
            }
    };
    strcpy(self->results, "");

    Tokenize(statementRequest, &token);

    if (strlen(token.command) < 1) {
        return -1; // error
    }

    switch (hashFunction(token.command)) {
        // CREATE TABLE
        case 0:
            createTableFunction(self, statementRequest, token);
            return 0;
        case 1:
            // INSERT INTO
            statementTokenValues(token.tokens, statementRequest, self->numTableColumns);
            executeInsertStatement(self, &token);
            strcpy(self->results, "success\n");
            return 0;
        case 2:
            // SELECT
            sprintf(self->results, "table\n");
            // row headers
            if (charPositionInString(0, '*', statementRequest)) {
                executeSelectAllTableHeaders(self);
            } else {
                int selectedColumns = numTableColumns(statementRequest);
                printf("num columns: %d", selectedColumns);
                char tokens[][10] = { "", "", "" };
                selectStatementTokenValues(tokens, statementRequest, selectedColumns);
                executeSelectTableHeaders(self, tokens, selectedColumns);
                strcat(self->results, "\n");
            }
            executeSelectTableValues(self);
            return 0; // retrieve columnHeader with SELECT
    }
    return 1; // error, should have attempted at least one valid statement
}
void Tokenize(const char *statementRequest, struct StatementTokens *token) {
    if (strlen(statementRequest) > 6) {
        strncpy(token->command, &statementRequest[0], 6);
        token->command[6] = '\0';
    }
}
// String Helper Functions
int charPositionInString(int initial_position, const char findChar, const char searchString[])
{
    int idx = 0;

    while (idx < strlen(searchString)) {
        if (searchString[initial_position + idx] == findChar )
        {
            break;
        }
        idx++;
    }
    // not found, return 0
    if (strlen(searchString) == idx) {
        return 0;
    }

    return initial_position + idx;
}
int statementTokenValues(char self[][10], const char* inputString, int selfArraySize)
{
    int startIdx = charPositionInString(0, '(', inputString) + 1;
    int endIdx = charPositionInString(startIdx, ' ', inputString);
    if (endIdx == 0) {
        endIdx = strlen(inputString);
    }

    int stringLength = endIdx - startIdx;
    strncpy(self[0], &inputString[startIdx], stringLength);

    for (int i = 1; i < selfArraySize; i++) {
        int commaIdx = charPositionInString(startIdx, ',', inputString) + 1;
        int commaSpaceIdx = charPositionInString(commaIdx, ' ', inputString);
        if (commaSpaceIdx == 0) {
            commaSpaceIdx = strlen(inputString) - 2;
        }
        strncpy(self[i], &inputString[commaIdx], commaSpaceIdx - commaIdx);
        self[i][commaSpaceIdx - commaIdx + 1] = '\0';
        startIdx = commaIdx;
    }

    return 0;
}
int selectStatementTokenValues(char self[][10], const char* inputString, int selfArraySize)
{
    int startIdx = charPositionInString(0, ' ', inputString);
    for (int i = 0; i < selfArraySize; i++) {
        int commaDelimiterIdx = charPositionInString(startIdx + 1, ',', inputString);
        int chooseNextDelimiterIdx;
        if (commaDelimiterIdx) {
            chooseNextDelimiterIdx = commaDelimiterIdx;
        }
        else {
            chooseNextDelimiterIdx = charPositionInString(startIdx + 1, ' ', inputString);
        }
        strncpy(self[i], &inputString[startIdx + 1],  chooseNextDelimiterIdx - (startIdx + 1));
        self[i][chooseNextDelimiterIdx - startIdx] = '\0';
        startIdx = chooseNextDelimiterIdx;
    }

    return 0;
}
// String Helper Functions
void executeCreateTableStatement(const struct ParserSelf *self, struct StatementTokens *token) {
    for (int i = 0; i < self->numTableColumns; i++) {
        strcpy(self->columnHeaders[i], token->tokens[i]);
    }
}
void executeInsertStatement(struct ParserSelf *self, struct StatementTokens *token) {
    for (int i = 0; i < self->numTableColumns; i++) {
        char *ptr = token->tokens[i];
        self->columnValues[i] = strtol(token->tokens[i], &ptr, 10);
    }
}
void executeSelectTableValues(struct ParserSelf *self) {// goto next line if row values exist
    if (self->columnValues[0] != 0) {
        strcat(self->results, "\n");
    }
    // print row values
    for (int i = 0; i < self->numTableColumns; i++) {
        if (self->columnValues[i] != 0) {
            char currentRowValues[10] = "";
            sprintf(currentRowValues, "%d", self->columnValues[i]);
            // do not add \t to last entry
            if (i < self->numTableColumns - 1) {
                strcat(currentRowValues, "\t");
            }
            strcat(self->results, currentRowValues);
        }
    }
}
void executeSelectAllTableHeaders(struct ParserSelf *self) {
    for(int i = 0; i < self->numTableColumns; i++) {

        char* currentRow = self->columnHeaders[i];
        // do not add \t to last entry
        if (i < self->numTableColumns - 1) {
            strcat(currentRow, "\t");
        }
        strcat(self->results, currentRow);
    }
}
void executeSelectTableHeaders(struct ParserSelf *self, char tableHeaders[10][10], int tableHeadersSize) {
    for(int i = 0; i < tableHeadersSize; i++) {

        char* currentRow = tableHeaders[i];
        // do not add \t to last entry
        if (i < tableHeadersSize - 1) {
            strcat(currentRow, "\t");
        }
        strcat(self->results, currentRow);
    }
}
int numTableColumns(const char *printedString) {
    int startIdx = 1, commaIdx = 0, numEntries = 0;
    while(startIdx != 0) {
        startIdx = charPositionInString(commaIdx + 1, ',', printedString);
        commaIdx = startIdx;
        numEntries++;
    }
    return numEntries;
}
