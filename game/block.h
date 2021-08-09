#pragma once
#include "../utils/types.h"
#include "../utils/vector.h"
#include "../utils/default.h"
#include "../logic/color.h"

typedef u32 gm_BlockId;

typedef struct {
    char* block_name;
    bool solid;
    vx_Color3 color;

    /*  Other data: custom mesh, gravity/physics data...    */
} gm_Block;

gm_Block gm_block_new(char*, bool, vx_Color3);

_VX_OPTION_CREATE_PROT_FOR_TYPE(gm_BlockId);
_VX_OPTION_CREATE_PROT_FOR_TYPE(gm_Block);
_VX_VECTOR_CREATE_PROT_FOR_TYPE(gm_Block);

typedef struct {
    VX_VECTOR(gm_Block) blocks;

    /*  Other stuff */
} gm_BlockManager;

gm_BlockManager gm_block_manager_new();
void gm_block_manager_free(gm_BlockManager*);

#define GM_BLOCK_MANAGER_DATA(_MAN_PTR) VX_VECTOR_DATA(gm_Block, &((_MAN_PTR)->blocks))
#define GM_BLOCK_MANAGER_BLOCK_NUM(_MAN_PTR) (_MAN_PTR)->blocks.length

gm_BlockId gm_block_manager_push_block(gm_BlockManager*, gm_Block);
VX_T(gm_BlockId, vx_Option) gm_block_manager_get_block_by_name(gm_BlockManager*, char*);
gm_Block* gm_block_manager_get_block_ptr_by_name(gm_BlockManager*, char*);
void gm_block_manager_push_standard_color_blocks(gm_BlockManager*);
