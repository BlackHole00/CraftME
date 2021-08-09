#include "block.h"
#include <string.h>
#include <stdio.h>

gm_Block gm_block_new(char* name, bool solid, vx_Color3 color) {
    gm_Block block;

    block.block_name = name;
    block.color = color;
    block.solid = solid;

    return block;
}

gm_BlockManager gm_block_manager_new() {
    gm_BlockManager manager;

    manager.blocks = vx_vector_new();

    gm_Block air = gm_block_new("air", false, VX_COLOR3_NEW(0.0f, 0.0f, 0.0f));
    gm_block_manager_push_block(&manager, air);

    return manager;
}

void gm_block_manager_free(gm_BlockManager* manager) {
    vx_vector_free(&manager->blocks);
}

gm_BlockId gm_block_manager_push_block(gm_BlockManager* manager, gm_Block block) {
    u32 id = manager->blocks.length;

    VX_T(gm_Block, vx_vector_push)(&manager->blocks, block);

    return id;
}

VX_T(gm_BlockId, vx_Option) gm_block_manager_get_block_by_name(gm_BlockManager* manager, char* name) {
    VX_T(gm_BlockId, vx_Option) id = VX_T(gm_BlockId, vx_option_none)();

    for (u32 i = 0; i < manager->blocks.length; i++) {
        if (strcmp(VX_VECTOR_DATA(gm_Block, &manager->blocks)[i].block_name, name) == 0) {
            id = VX_T(gm_BlockId, vx_option_some)(i);
            break;
        }
    }

    return id;
}

gm_Block* gm_block_manager_get_block_ptr_by_name(gm_BlockManager* manager, char* name) {
    gm_Block* block = NULL;

    for (u32 i = 0; i < manager->blocks.length; i++) {
        if (strcmp(VX_VECTOR_DATA(gm_Block, &manager->blocks)[i].block_name, name) == 0) {
            block = &VX_VECTOR_DATA(gm_Block, &manager->blocks)[i];
            break;
        }
    }

    return block;
}

void gm_block_manager_push_standard_color_blocks(gm_BlockManager* manager) {
    gm_Block block = gm_block_new("red", true, VX_COLOR3_NEW(1.0f, 0.0f, 0.0f));
    gm_block_manager_push_block(manager, block);

    block = gm_block_new("yellow", true, VX_COLOR3_NEW(1.0f, 1.0f, 0.0f));
    gm_block_manager_push_block(manager, block);

    block = gm_block_new("green", true, VX_COLOR3_NEW(0.0f, 1.0f, 0.0f));
    gm_block_manager_push_block(manager, block);

    block = gm_block_new("light_blue", true, VX_COLOR3_NEW(0.0f, 1.0f, 1.0f));
    gm_block_manager_push_block(manager, block);

    block = gm_block_new("blue", true, VX_COLOR3_NEW(0.0f, 0.0f, 1.0f));
    gm_block_manager_push_block(manager, block);

    block = gm_block_new("purple", true, VX_COLOR3_NEW(1.0f, 0.0f, 1.0f));
    gm_block_manager_push_block(manager, block);

    block = gm_block_new("white", true, VX_COLOR3_NEW(1.0f, 1.0f, 1.0f));
    gm_block_manager_push_block(manager, block);

    block = gm_block_new("black", true, VX_COLOR3_NEW(0.0f, 0.0f, 0.0f));
    gm_block_manager_push_block(manager, block);

    block = gm_block_new("brown", true, VX_COLOR3_NEW(0.45f, 0.25f, 0.15f));
    gm_block_manager_push_block(manager, block);

    block = gm_block_new("dark_green", true, VX_COLOR3_NEW(0.04f, 0.25f, 0.01f));
    gm_block_manager_push_block(manager, block);

    block = gm_block_new("gray", true, VX_COLOR3_NEW(0.75f, 0.75f, 0.75f));
    gm_block_manager_push_block(manager, block);
}

_VX_OPTION_CREATE_BODY_FOR_TYPE(gm_BlockId);
_VX_OPTION_CREATE_BODY_FOR_TYPE(gm_Block);
_VX_VECTOR_CREATE_BODY_FOR_TYPE(gm_Block);
