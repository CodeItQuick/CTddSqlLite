//
// Created by Owner on 4/7/2024.
//

#pragma once

struct ParserSelf {
    char results[50];
    char columnHeader[50];
    int columnValue;
};

int findString(int pos, const char charStr, const char* searchString);
int findColumnLabel(char* self, const char* inputString);
int parse(struct ParserSelf* self, const char* printedString);
