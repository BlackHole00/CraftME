#pragma once
#include "chunk.h"
#include "block.h"
#include "../utils/types.h"
#include "../gfx/buffer.h"

#define GM_CHUNK_DIM_X 16
#define GM_CHUNK_DIM_Y 16
#define GM_CHUNK_DIM_Z 16

typedef struct {
    gm_BlockId blocks[GM_CHUNK_DIM_X][GM_CHUNK_DIM_Y][GM_CHUNK_DIM_Z];

    /*  Other data: biome, temperature, gameplay flags... Idk...    */
} gm_Chunk;

gm_Chunk gm_chunk_new();

/*  To access blocks more easily... equivalento to do chunk_ptr->blocks */
#define GM_CHUNK_DATA(_CHUNK_PTR) ((_CHUNK_PTR)->blocks)

/*
    0 = front
    1 = rear
    2 = left
    3 = right
    4 = top
    5 = bottom
*/
void gm_chunk_write_to_buffer(gm_Chunk*, vx_Buffer*, gm_BlockManager*, gm_Chunk*[6]);
void gm_chunk_gen(gm_Chunk*, gm_BlockManager*, u32, u32, u32);
void gm_chunk_gen_random(gm_Chunk*, u32);
