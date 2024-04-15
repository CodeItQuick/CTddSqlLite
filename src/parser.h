//
// Created by Owner on 4/7/2024.
//

#pragma once

struct ParserSelf {
    char results[50];
    char columnHeaders[10][50];
    int columnValues[10];
    int numEntries;
};

struct StatementTokens {
    char command[7];
    char tokens[10][50];
};

int findString(int pos, const char charStr, const char* searchString);
int findColumnLabel(char self[][50], const char* inputString, int selfArraySize);
int parse(struct ParserSelf* self, const char* statementRequest);

int numTableColumns(const char *printedString);

void executeCreateTableStatement(const struct ParserSelf *self, struct StatementTokens *tokens);

void executeInsertStatement(struct ParserSelf *self, struct StatementTokens *token);

void executeSelectTableHeaders(struct ParserSelf *self);

void executeSelectTableValues(struct ParserSelf *self);

void Tokenize(const char *statementRequest, struct StatementTokens *token);
