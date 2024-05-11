//
// Created by Owner on 4/7/2024.
//

#pragma once

struct ParserSelf {
    char results[50];
    char *columnHeaders[10];
    int columnValues[10];
    int numTableColumns;
};

struct StatementTokens {
    char command[7];
    char tokens[10][10];
};

int charPositionInString(int initial_position, char findChar, const char* searchString);
int statementTokenValues(char self[][10], const char* inputString, int selfArraySize);
int selectStatementTokenValues(char self[][10], const char* inputString, int selfArraySize);
int parse(struct ParserSelf* self, const char* statementRequest);

int numTableColumns(const char *printedString);

void executeCreateTableStatement(const struct ParserSelf *self, struct StatementTokens *tokens);

void executeInsertStatement(struct ParserSelf *self, struct StatementTokens *token);

void executeSelectAllTableHeaders(struct ParserSelf *self);
void executeSelectTableHeaders(struct ParserSelf *self, char tableHeaders[10][10], int tableHeadersSize);

void executeSelectTableValues(struct ParserSelf *self);

void Tokenize(const char *statementRequest, struct StatementTokens *token);
