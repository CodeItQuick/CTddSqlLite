//
// Created by Owner on 4/7/2024.
//

#pragma once

struct ParserSelf {
    char results[50];
    char columnHeader[50];
    int columnValue;
};

int substring(char* substr, int len, const char* string, int pos);
int findString(int pos, const char charStr, const char* searchString);
int findColumnLabel(const char* inputString, char* columnLabel);
int parse(struct ParserSelf* self, const char* printedString);
