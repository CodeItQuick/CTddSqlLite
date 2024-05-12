//
// Created by Owner on 5/11/2024.
//
#include <stdio.h>
#include <string.h>
#include "command_reader.h"

char* command_reader(char** commands) {
    char* const command = commands[0];
    if (strlen(commands[0]) > 0) {
        commands = commands[1];
    }
    return command;
}
