#include <stdio.h>
#include "parser.h"
#include "repl.h"


int main() {
    char columnHeader[10][10] = {
            "", "", "", "", "",
            "", "", "", "", ""
    };
    struct ParserSelf self = { "",
                               columnHeader[0], columnHeader[1], columnHeader[2],
                               columnHeader[3], columnHeader[4], columnHeader[5],
                               columnHeader[6], columnHeader[7], columnHeader[8],
                               columnHeader[9] };
    struct replCommands replCommands = {};
    repl(replCommands, &self);
    return 0;
}

