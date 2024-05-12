//
// Created by Owner on 5/12/2024.
//

#include <string.h>
#include "repl.h"
#include "parser.h"

int repl(struct replCommands commands, struct ParserSelf *self) {

    // first input
    parse(self, commands.commands[0]);
    char strResults[50] = "";
    strcpy(strResults, self->results);

    // remaining inputs, up to 5 total
    for (int i = 1; i < 5; ++i) {
        if (strlen(commands.commands[i])) {
            parse(self, commands.commands[1]);
            strcat(strResults, self->results);
            strcat(strResults, "\n");
            strcpy(self->results, strResults);
        }
    }

    return 0;
}