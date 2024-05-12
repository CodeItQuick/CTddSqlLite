//
// Created by Owner on 5/12/2024.
//

#include "repl.h"
#include "parser.h"

int repl(struct replCommands commands) {
    char columnHeader[10][10] = {
            "", "", "", "", "",
            "", "", "", "", ""
    };
    struct ParserSelf self = { "",
                               columnHeader[0], columnHeader[1], columnHeader[2],
                               columnHeader[3], columnHeader[4], columnHeader[5],
                               columnHeader[6], columnHeader[7], columnHeader[8],
                               columnHeader[9] };

    int result = parse(&self, commands.commands[0]);
    return result;
}