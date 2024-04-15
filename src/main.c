#include <stdio.h>
#include "parser.h"



int main() {

    struct ParserSelf self = {
            "",
            {
                    "", "", "", "", "",
                    "", "", "", "", ""
            },
            {
                    0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0
            }
    };
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

