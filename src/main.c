#include <stdio.h>
#include "parser.h"



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
    char createTable[] = "CREATE TABLE default (ID int,Age int);\n";
    parse(&self, createTable);
    printf("%s", self.results);
    char insertValues[] = "INSERT INTO default VALUES (1,17);\n";
    parse(&self, insertValues);
    printf("%s", self.results);
    char selectStatement[] = "SELECT * FROM default;";
    parse(&self, selectStatement);
    printf("%s", self.results);
    return 0;
}

