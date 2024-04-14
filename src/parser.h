//
// Created by Owner on 4/7/2024.
//

#pragma once

struct ParserSelf {
    char results[50];
    char columnHeader[50];
    int columnValue;
    char columnHeaderTwo[50];
};

int findString(int pos, const char charStr, const char* searchString);
int findColumnLabel(char self[][50], const char* inputString, int selfArraySize);
int parse(struct ParserSelf* self, const char* printedString);
