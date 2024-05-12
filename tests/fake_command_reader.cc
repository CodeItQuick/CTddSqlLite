//
// Created by Owner on 5/11/2024.
//
#include <stdio.h>
#include <string.h>
#include "fake_command_reader.h"

char* commands_reader(struct commands commands, int len) {
    char* const firstCommand = commands.commandList[len];
    return firstCommand;
}
