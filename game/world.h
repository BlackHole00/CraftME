#pragma once
#include "../gfx/mesh.h"
#include "../logic/transform.h"
#include "chunk.h"

#define GM_CHUNK_SCALE_X 0.5f
#define GM_CHUNK_SCALE_Y 0.5f
#define GM_CHUNK_SCALE_Z 0.5f

#define GM_WORLD_POS_TO_INDEX(_RND_DTS, _X, _Y, _Z) ((_Z) * _RND_DTS * _RND_DTS +  (_Y) * _RND_DTS +  (_X))

typedef struct {
    /*  For now only used to determinate what chunks to draw... No infinite world yet... */
    vx_Position* player_position;
    vx_Rotation* player_rotation;

    u32 render_distance;

    /*  We do not need a vx_Vector, only a simple dynamically allocated array.  */
    gm_Chunk* chunks;
    vx_Mesh* meshes;

    vx_Layout layout;

    gm_BlockManager block_manager;

    /*  DEBUG STUFF */
    /* TODO (#1#): Actually implement chunk borders */
    bool show_chunk_borders;
    vx_Buffer chunk_borders;
} gm_World;

gm_World gm_world_new(u32);
gm_World gm_world_from_block_manager(u32, gm_BlockManager);
void gm_world_free(gm_World*);

void gm_world_gen_chunks(gm_World*);
void gm_world_gen_all_meshes(gm_World*);
void gm_world_regen_chunk_mesh(gm_World*, u32, u32, u32);
void gm_world_draw(gm_World*);
