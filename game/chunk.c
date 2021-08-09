#include "chunk.h"
#include <string.h>
#include <stdlib.h>

#define CUBE_FACE_FRONT(BUFF, X, Y, Z) vx_buffer_push_3(BUFF, X - 0.5f,  Y - 0.5f, Z - 0.5f);\
vx_buffer_push_3(BUFF, X + 0.5f,  Y - 0.5f, Z - 0.5f);\
vx_buffer_push_3(BUFF, X + 0.5f,  Y + 0.5f, Z - 0.5f);\
vx_buffer_push_3(BUFF, X - 0.5f,  Y + 0.5f, Z - 0.5f);

#define CUBE_FACE_REAR(BUFF, X, Y, Z) vx_buffer_push_3(BUFF, X - 0.5f,  Y - 0.5f, Z + 0.5f);\
vx_buffer_push_3(BUFF, X - 0.5f,  Y + 0.5f, Z + 0.5f);\
vx_buffer_push_3(BUFF, X + 0.5f,  Y + 0.5f, Z + 0.5f);\
vx_buffer_push_3(BUFF, X + 0.5f,  Y - 0.5f, Z + 0.5f);

#define CUBE_FACE_LEFT(BUFF, X, Y, Z) vx_buffer_push_3(BUFF, X - 0.5f,  Y - 0.5f, Z - 0.5f);\
vx_buffer_push_3(BUFF, X - 0.5f,  Y + 0.5f, Z - 0.5f);\
vx_buffer_push_3(BUFF, X - 0.5f,  Y + 0.5f, Z + 0.5f);\
vx_buffer_push_3(BUFF, X - 0.5f,  Y - 0.5f, Z + 0.5f);

#define CUBE_FACE_RIGHT(BUFF, X, Y, Z) vx_buffer_push_3(BUFF, X + 0.5f,  Y - 0.5f, Z - 0.5f);\
vx_buffer_push_3(BUFF, X + 0.5f,  Y - 0.5f, Z + 0.5f);\
vx_buffer_push_3(BUFF, X + 0.5f,  Y + 0.5f, Z + 0.5f);\
vx_buffer_push_3(BUFF, X + 0.5f,  Y + 0.5f, Z - 0.5f);

#define CUBE_FACE_TOP(BUFF, X, Y, Z) vx_buffer_push_3(BUFF, X - 0.5f,  Y + 0.5f, Z - 0.5f);\
vx_buffer_push_3(BUFF, X + 0.5f,  Y + 0.5f, Z - 0.5f);\
vx_buffer_push_3(BUFF, X + 0.5f,  Y + 0.5f, Z + 0.5f);\
vx_buffer_push_3(BUFF, X - 0.5f,  Y + 0.5f, Z + 0.5f);

#define CUBE_FACE_BOTTOM(BUFF, X, Y, Z) vx_buffer_push_3(BUFF, X - 0.5f,  Y - 0.5f, Z + 0.5f);\
vx_buffer_push_3(BUFF, X + 0.5f,  Y - 0.5f, Z + 0.5f);\
vx_buffer_push_3(BUFF, X + 0.5f,  Y - 0.5f, Z - 0.5f);\
vx_buffer_push_3(BUFF, X - 0.5f,  Y - 0.5f, Z - 0.5f);

#define PSEUDO_UV_FRONT_REAR(BUFF, R, G, B) vx_buffer_hint_color3(BUFF,\
    ((R - 0.065f < 0.0f) ? R : R - 0.065f),\
    ((G - 0.065f < 0.0f) ? G : G - 0.065f),\
    ((B - 0.065f < 0.0f) ? B : B - 0.065f)\
)

#define PSEUDO_UV_LEFT_RIGHT(BUFF, R, G, B) vx_buffer_hint_color3(BUFF,\
    ((R - 0.095f < 0.0f) ? R : R - 0.095f),\
    ((G - 0.095f < 0.0f) ? G : G - 0.095f),\
    ((B - 0.095f < 0.0f) ? B : B - 0.095f)\
)

#define PSEUDO_UV_TOP_BOTTOM(BUFF, R, G, B) vx_buffer_hint_color3(BUFF, R, G, B)


gm_Chunk gm_chunk_new() {
    gm_Chunk chunk;

    /*  block id 0 is air   */
    memset(&chunk.blocks, 0, sizeof(gm_BlockId) * GM_CHUNK_DIM_X * GM_CHUNK_DIM_Y * GM_CHUNK_DIM_Z);

    return chunk;
}

void gm_chunk_write_to_buffer(gm_Chunk* chunk, vx_Buffer* buffer, gm_BlockManager* block_manager, gm_Chunk* near_chunks[6]) {
    for (u32 x = 0; x < GM_CHUNK_DIM_X; x++) {
        for (u32 y = 0; y < GM_CHUNK_DIM_Y; y++) {
            for (u32 z = 0; z < GM_CHUNK_DIM_X; z++) {
                gm_BlockId current_id = chunk->blocks[x][y][z];

                if (GM_BLOCK_MANAGER_DATA(block_manager)[current_id].solid) {
                    vx_Color3 block_color = GM_BLOCK_MANAGER_DATA(block_manager)[current_id].color;

                    if ((z <= 0 && near_chunks[0] == NULL) ||
                        (z <= 0 && !GM_BLOCK_MANAGER_DATA(block_manager)[((near_chunks[0])->blocks)[x][y][GM_CHUNK_DIM_Z - 1]].solid) ||
                        (z >  0 && !GM_BLOCK_MANAGER_DATA(block_manager)[chunk->blocks[x][y][z - 1]].solid)
                    ) {
                        PSEUDO_UV_FRONT_REAR(buffer, block_color.r, block_color.g, block_color.b);
                        CUBE_FACE_FRONT     (buffer, x, y, z);
                    }

                    if ((z >= (GM_CHUNK_DIM_Z - 1) && near_chunks[1] == NULL) ||
                        (z >= (GM_CHUNK_DIM_Z - 1) && !GM_BLOCK_MANAGER_DATA(block_manager)[((near_chunks[1])->blocks)[x][y][0]].solid) ||
                        (z <  (GM_CHUNK_DIM_Z - 1) && !GM_BLOCK_MANAGER_DATA(block_manager)[chunk->blocks[x][y][z + 1]].solid)
                    ) {
                        PSEUDO_UV_FRONT_REAR(buffer, block_color.r, block_color.g, block_color.b);
                        CUBE_FACE_REAR      (buffer, x, y, z);
                    }

                    if ((x <= 0 && near_chunks[2] == NULL) ||
                        (x <= 0 && !GM_BLOCK_MANAGER_DATA(block_manager)[((near_chunks[2])->blocks)[GM_CHUNK_DIM_X - 1][y][z]].solid) ||
                        (x >  0 && !GM_BLOCK_MANAGER_DATA(block_manager)[chunk->blocks[x - 1][y][z]].solid)
                    ) {
                        PSEUDO_UV_LEFT_RIGHT(buffer, block_color.r, block_color.g, block_color.b);
                        CUBE_FACE_LEFT      (buffer, x, y, z);
                    }

                    if ((x >= (GM_CHUNK_DIM_X - 1) && near_chunks[3] == NULL) ||
                        (x >= (GM_CHUNK_DIM_X - 1) && !GM_BLOCK_MANAGER_DATA(block_manager)[((near_chunks[3])->blocks)[0][y][z]].solid) ||
                        (x <  (GM_CHUNK_DIM_X - 1) && !GM_BLOCK_MANAGER_DATA(block_manager)[chunk->blocks[x + 1][y][z]].solid)
                    ) {
                        PSEUDO_UV_LEFT_RIGHT(buffer, block_color.r, block_color.g, block_color.b);
                        CUBE_FACE_RIGHT     (buffer, x, y, z);
                    }

                    if ((y <= 0 && near_chunks[4] == NULL) ||
                        (y <= 0 && !GM_BLOCK_MANAGER_DATA(block_manager)[((near_chunks[4])->blocks)[x][GM_CHUNK_DIM_Y - 1][z]].solid) ||
                        (y >  0 && !GM_BLOCK_MANAGER_DATA(block_manager)[chunk->blocks[x][y - 1][z]].solid)
                    ) {
                        PSEUDO_UV_TOP_BOTTOM(buffer, block_color.r, block_color.g, block_color.b);
                        CUBE_FACE_BOTTOM    (buffer, x, y, z);
                    }

                    if ((y >= (GM_CHUNK_DIM_Y - 1) && near_chunks[5] == NULL) ||
                        (y >= (GM_CHUNK_DIM_Y - 1) && !GM_BLOCK_MANAGER_DATA(block_manager)[((near_chunks[5])->blocks)[x][0][z]].solid) ||
                        (y <  (GM_CHUNK_DIM_Y - 1) && !GM_BLOCK_MANAGER_DATA(block_manager)[chunk->blocks[x][y + 1][z]].solid)
                    ) {
                        PSEUDO_UV_TOP_BOTTOM(buffer, block_color.r, block_color.g, block_color.b);
                        CUBE_FACE_TOP       (buffer, x, y, z);
                    }
                }
            }
        }
    }
}

void gm_chunk_gen_random(gm_Chunk* chunk, u32 block_num) {
    for (u32 x = 0; x < GM_CHUNK_DIM_X; x++) {
        for (u32 y = 0; y < GM_CHUNK_DIM_X; y++) {
            for (u32 z = 0; z < GM_CHUNK_DIM_X; z++) {
                u32 not_air = rand() % 30;

                /*  1 in 30 chance to put a block   */
                if (not_air == 0) {
                    GM_CHUNK_DATA(chunk)[x][y][z] = rand() % (block_num - 1) + 1;
                }
            }
        }
    }
}

void gm_chunk_gen(gm_Chunk* chunk, gm_BlockManager* bmanager, u32 x, u32 y, u32 z) {
    gm_BlockId grass_id     = VX_T(gm_BlockId, vx_option_unwrap)(gm_block_manager_get_block_by_name(bmanager, "green"));
    gm_BlockId log_id       = VX_T(gm_BlockId, vx_option_unwrap)(gm_block_manager_get_block_by_name(bmanager, "brown"));
    gm_BlockId leaves_id    = VX_T(gm_BlockId, vx_option_unwrap)(gm_block_manager_get_block_by_name(bmanager, "dark_green"));
    gm_BlockId stone_id     = VX_T(gm_BlockId, vx_option_unwrap)(gm_block_manager_get_block_by_name(bmanager, "gray"));
    gm_BlockId water_id     = VX_T(gm_BlockId, vx_option_unwrap)(gm_block_manager_get_block_by_name(bmanager, "blue"));

    if (y <= 0) {   /*  Underground */
        for (u32 x = 0; x < GM_CHUNK_DIM_X; x++) {
            for (u32 y = 0; y < GM_CHUNK_DIM_Y; y++) {
                for (u32 z = 0; z < GM_CHUNK_DIM_Z; z++) {
                    GM_CHUNK_DATA(chunk)[x][y][z] = stone_id;
                }
            }
        }
    } else if (y == 1) {    /*  Normal terrain  */
        /*  Grass   */
        u32 y_level = rand() % 3 + 1;
        for (u32 x = 0; x < GM_CHUNK_DIM_X; x++) {
            for (u32 y = 0; y <= y_level; y++) {
                for (u32 z = 0; z < GM_CHUNK_DIM_Z; z++) {
                    GM_CHUNK_DATA(chunk)[x][y][z] = grass_id;
                }
            }
        }

        /*  Tree    */
        for (u32 y = 2; y < 5; y++) {
            GM_CHUNK_DATA(chunk)[2][y][2] = log_id;
        }
        for (u32 y = 5; y <= 7; y++) {
            for (u32 x = 1; x <= 3; x++) {
                for (u32 z = 1; z <= 3; z++) {
                    GM_CHUNK_DATA(chunk)[x][y][z] = leaves_id;
                }
            }
        }

        /*  Lake    */
        for (u32 x = 8; x < 14; x++) {
            for (u32 z = 10; z < 14; z++) {
                GM_CHUNK_DATA(chunk)[x][y_level][z] = water_id;
            }
        }
    } else if (y >= 2){    /*  Clouds  */
        u32 cloud_x = rand() % 13 + 2;
        u32 cloud_y = rand() % 4 + 10;

        for (u32 x = cloud_x; x < cloud_x + 2; x++) {
            for (u32 z = cloud_x; z < cloud_x + 2; z++) {
                GM_CHUNK_DATA(chunk)[x][cloud_y][z] = stone_id;
            }
        }
    }
}
