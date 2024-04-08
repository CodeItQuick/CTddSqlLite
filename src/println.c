//
// Created by Owner on 4/7/2024.
//
#include <stdio.h>
#include "println.h"

char * println(char *printedString) {
    printf("%s", printedString);
    return printedString;
}