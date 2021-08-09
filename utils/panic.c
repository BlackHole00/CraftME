#include "panic.h"
#include <stdio.h>
#include <stdlib.h>

void vx_panic(char* file, int line, const char* function, char* message) {
    printf("Error in function %s(%s::%d): %s", function, file, line, message);
    exit(-1);
}
