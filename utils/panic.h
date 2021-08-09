#pragma once

#define VX_PANIC(_MESSAGE) vx_panic(__FILE__, __LINE__, __PRETTY_FUNCTION__, _MESSAGE)
#define VX_ASSERT(_MESSAGE, _EQ) { if(!(_EQ)) { VX_PANIC(_MESSAGE); } }
#define VX_PANIC_EXIT_OP(_MESSAGE, _EXIT_OP) _EXIT_OP; VX_PANIC(_MESSAGE);
#define VX_ASSERT_EXIT_OP(_MESSAGE, _EQ, _EXIT_OP) { if(!(_EQ)) { VX_PANIC_EXIT_OP(_MESSAGE, _EXIT_OP); } }

void vx_panic(char*, int, const char*, char*);
