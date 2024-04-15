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

int findString(int pos, const char charStr, const char* searchString);
int findColumnLabel(char self[][50], const char* inputString, int selfArraySize);
int parse(struct ParserSelf* self, const char* printedString);

int numEntriesInStatement(const char *printedString);

void executeCreateTableStatement(const struct ParserSelf *self, const char *printedString);

void executeInsertSingleEntry(struct ParserSelf *self, const char *printedString);

void executeInsertMultipleEntries(struct ParserSelf *self, const char *printedString);

void executeSelectTableHeaders(struct ParserSelf *self);

void executeSelectTableValues(struct ParserSelf *self);
