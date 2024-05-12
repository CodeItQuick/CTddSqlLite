//
// Created by Owner on 5/12/2024.
//

#include <string.h>
#include "repl.h"
#include "parser.h"

int repl(struct replCommands commands, struct ParserSelf *self) {

    int result = parse(self, commands.commands[0]);
    char strResults[50] = "";
    strcpy(strResults, self->results);
    if (strlen(commands.commands[1])) {
        parse(self, commands.commands[1]);
        strcat(strResults, self->results);
        strcpy(self->results, strResults);
    }
    return result;
}