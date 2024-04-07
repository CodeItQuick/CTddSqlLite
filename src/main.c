#include <stdio.h>
#include "main.h"


int main() {
    char helloWorld[] = "Hello, World!\n";
    println(helloWorld);
    return 0;
}

char * println(char *printedString) {
    printf("%s", printedString);
    return printedString;
}
