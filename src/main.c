#include "parser.h"


int main() {
    char helloWorld[] = "Hello, World!\n";
    struct ParserSelf* self;
    parse(self, helloWorld);
    return 0;
}

