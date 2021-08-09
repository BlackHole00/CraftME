#include "mem.h"
#include <malloc.h>
#include "panic.h"

void* vx_smalloc(usize size) {
    void* ptr = malloc(size);
    VX_ASSERT("Could not allocate memory!", ptr != 0 || size == 0);
    return ptr;
}

void* vx_srealloc(void* mem_adr, usize size) {
    void* ptr = realloc(mem_adr, size);
    VX_ASSERT("Could not reallocate memory!", ptr != 0 || size == 0);
    return ptr;
}
