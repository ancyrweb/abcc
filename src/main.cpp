#include <iostream>
#include "Compiler.h"

int main() {
    Compiler compiler;
    compiler.readFromFile("../main-test.c");
    return 0;
}
