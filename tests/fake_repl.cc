//
// Created by Owner on 5/11/2024.
//

#include "fake_repl.h"

char* command_reader(char** commands) {
    char* const command = "CREATE TABLE default (ID int);";
    return &command[0];
}
