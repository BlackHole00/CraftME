#pragma once
#include "../utils/types.h"
#include "../utils/vector.h"
#include "../logic/vec.h"
#include "camera.h"

typedef struct {
    struct {
        bool wireframe: 1;
        bool cull: 1;
        bool depth_test: 1;
        bool clear: 1;
        
        VX_T(f32, vx_Vec4) clear_color;
    } flags;

    bool should_update_flags;
    bool should_update_camera;

    VX_VECTOR(vx_Camera) camera_stack; 
} vx_Renderer;

vx_Renderer vx_renderer_new();
void vx_renderer_free(vx_Renderer*);

void vx_renderer_clearscr(vx_Renderer*);
void vx_renderer_draw_preparation(vx_Renderer*);

void vx_renderer_set_wireframe(vx_Renderer*, bool);
void vx_renderer_set_cull(vx_Renderer*, bool);
void vx_renderer_set_depth_test(vx_Renderer*, bool);
void vx_renderer_set_clear(vx_Renderer*, bool);

void vx_renderer_push_camera(vx_Renderer*, vx_Camera);
void vx_renderer_push_new_camera(vx_Renderer*);
VX_T(vx_Camera, vx_Option) vx_renderer_pop_camera(vx_Renderer*);
vx_Camera* vx_renderer_get_current_camera(vx_Renderer*);

/* TODO (#1#): Add draw functios and use should_update_camera */
