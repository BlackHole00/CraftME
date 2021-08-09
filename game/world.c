#include "world.h"
#include "../utils/mem.h"
#include <stdio.h>

gm_World gm_world_new(u32 render_distance) {
    gm_BlockManager manager = gm_block_manager_new();
    return gm_world_from_block_manager(render_distance, manager);
}

gm_World gm_world_from_block_manager(u32 render_distance, gm_BlockManager block_manager) {
    gm_World world;

    world.render_distance = render_distance;
    world.player_position = NULL;
    world.player_rotation = NULL;
    world.block_manager = block_manager;

    world.chunks = vx_smalloc(render_distance * render_distance * render_distance * sizeof(gm_Chunk));
    world.meshes = vx_smalloc(render_distance * render_distance * render_distance * sizeof(vx_Mesh));

    world.show_chunk_borders = false;
    world.chunk_borders = vx_buffer_new();
    vx_buffer_hint_color3(&world.chunk_borders, 1.0, 0.0, 0.0);

    for (u32 x = 0; x < render_distance; x++) {
        for (u32 y = 0; y < render_distance; y++) {
            for (u32 z = 0; z < render_distance; z++) {
                world.chunks[GM_WORLD_POS_TO_INDEX(render_distance, x, y, z)] = gm_chunk_new(); 
                world.meshes[GM_WORLD_POS_TO_INDEX(render_distance, x, y, z)] = vx_mesh_new(GL_QUADS);
            }
        }
    } 

    world.layout = vx_layout_new();
    vx_layout_push(&world.layout, VX_POSITION_3F32);

    return world;
}

void gm_world_free(gm_World* world) {
    vx_layout_free(&world->layout);
    vx_buffer_free(&world->chunk_borders);
    gm_block_manager_free(&world->block_manager);
    free(world->chunks);
    free(world->meshes);
}

void gm_world_gen_chunks(gm_World* world) {
    for (u32 x = 0; x < world->render_distance; x++) {
        for (u32 y = 0; y < world->render_distance; y++) {
            for (u32 z = 0; z < world->render_distance; z++) {
                gm_chunk_gen(&world->chunks[GM_WORLD_POS_TO_INDEX(world->render_distance, x, y, z)], &world->block_manager, x, y, z);
                //gm_chunk_gen_random(&world->chunks[GM_WORLD_POS_TO_INDEX(world->render_distance, x, y, z)], GM_BLOCK_MANAGER_BLOCK_NUM(&world->block_manager));
            }
        }
    }
}

void gm_world_gen_all_meshes(gm_World* world) {
    for (u32 x = 0; x < world->render_distance; x++) {
        for (u32 y = 0; y < world->render_distance; y++) {
            for (u32 z = 0; z < world->render_distance; z++) {
                gm_world_regen_chunk_mesh(world, x, y, z);
            }
        }
    }
}

void gm_world_regen_chunk_mesh(gm_World* world, u32 x, u32 y, u32 z) {
    gm_Chunk* near_chunks[6];
    near_chunks[0] = (z <= 0                            ? NULL : &world->chunks[GM_WORLD_POS_TO_INDEX(world->render_distance, x, y, z - 1)]);
    near_chunks[1] = (z >= (world->render_distance - 1) ? NULL : &world->chunks[GM_WORLD_POS_TO_INDEX(world->render_distance, x, y, z + 1)]);
    near_chunks[2] = (x <= 0                            ? NULL : &world->chunks[GM_WORLD_POS_TO_INDEX(world->render_distance, x - 1, y, z)]);
    near_chunks[3] = (x >= (world->render_distance - 1) ? NULL : &world->chunks[GM_WORLD_POS_TO_INDEX(world->render_distance, x + 1, y, z)]);
    near_chunks[4] = (y <= 0                            ? NULL : &world->chunks[GM_WORLD_POS_TO_INDEX(world->render_distance, x, y - 1, z)]);
    near_chunks[5] = (y >= (world->render_distance - 1) ? NULL : &world->chunks[GM_WORLD_POS_TO_INDEX(world->render_distance, x, y + 1, z)]);

    gm_chunk_write_to_buffer(
        &world->chunks[GM_WORLD_POS_TO_INDEX(world->render_distance, x, y, z)], 
        &(world->meshes[GM_WORLD_POS_TO_INDEX(world->render_distance, x, y, z)].buffer),
        &world->block_manager,
        near_chunks
    );

    world->meshes[GM_WORLD_POS_TO_INDEX(world->render_distance, x, y, z)].position 
         = VX_POSITION_NEW(x * GM_CHUNK_DIM_X * GM_CHUNK_SCALE_X, y * GM_CHUNK_DIM_Y * GM_CHUNK_SCALE_Y, z * GM_CHUNK_DIM_Z * GM_CHUNK_SCALE_Z);
    world->meshes[GM_WORLD_POS_TO_INDEX(world->render_distance, x, y, z)].scale
         = VX_SCALE_NEW(0.5, 0.5, 0.5);
}

void gm_world_draw(gm_World* world) {
    for (u32 x = 0; x < world->render_distance; x++) {
        for (u32 y = 0; y < world->render_distance; y++) {
            for (u32 z = 0; z < world->render_distance; z++) {
                vx_mesh_draw(&world->meshes[GM_WORLD_POS_TO_INDEX(world->render_distance, x, y, z)],
                    &world->layout
                );
            }
        }
    }
}
