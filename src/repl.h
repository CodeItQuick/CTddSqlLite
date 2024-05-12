//
// Created by Owner on 5/12/2024.
//

#pragma once

#include "parser.h"

struct replCommands {
    char commands[5][40];
};

int repl(struct replCommands commands, struct ParserSelf *self);