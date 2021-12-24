#include <iostream>
#include <cstdio>
#include <cstring>
#include "StackVM.hpp"
using namespace std;

int main(int argc, char * argv[]) {
    // Pending: align string output, setting width of every segment.
    int program0[] = { // use 0 datamemory.
        ICONST, 99,
        PRINT,
        HALT
    };
    int program1[] = { // use 1 datamemory.
        ICONST, 99,
        GSTORE, 0,
        GLOAD, 0,
        PRINT,
        HALT
    };
    int functSum[] = {
        LOAD, -4,           // 0
        LOAD, -3,           // 2
        IADD,               // 4
        RET,                // 5
        ICONST, 5,          // 6 -- start here
        ICONST, 6,          // 8
        CALL, 0, 2,         // 10
        PRINT,              // 13
        HALT                // 14
    };
    int fibonacci[] = { // use 5 datamemory.
        ICONST, 1,
        GSTORE, 0,
        ICONST, 1,
        GSTORE, 1,
        ICONST, 0,
        GSTORE, 2,
        ICONST, 0,
        GSTORE, 3,
        ICONST, 12, // fib limit.
        GSTORE, 4,
        ICONST, 1,
        PRINT,
        ICONST, 1,
        PRINT,
        GLOAD, 0,
        GLOAD, 1,
        IADD,
        GSTORE, 2,
        GLOAD, 2,
        PRINT,
        GLOAD, 1,
        GSTORE, 0,
        GLOAD, 2,
        GSTORE, 1,
        ICONST, 1,
        GLOAD, 3,
        IADD,
        GSTORE, 3,
        GLOAD, 4,
        GLOAD, 3,
        ILT,
        BRT, 26,
        HALT
    };

    int factorial[] = {
        ICONST, 2,      // 0
        LOAD, -3,       // 2
        ILT,            // 4
        BRF, 10,        // 5
        ICONST, 1,      // 7
        RET,            // 9
        LOAD, -3,       // 10
        LOAD, -3,       // 12
        ICONST, 1,      // 14
        ISUB,           // 16
        CALL, 0, 1,     // 17
        IMUL,           // 20 
        RET,            // 21 
        ICONST, 10,      // 22
        CALL, 0, 1,     // 24 
        PRINT,          // 27
        HALT            // 28 
    };
    //VM vm(fibonacci, 0, 5);
    VM vm(factorial, 22, 0);
    //VM vm(functSum, 6, 0);
    if (argc == 2) {
        if (strcmp(argv[1], "trace") == 0) vm.trace = true;
    }
    vm.cpu();
    return 0;
}
