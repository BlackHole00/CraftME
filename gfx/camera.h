#pragma once
#include "../logic/vec.h"
#include "../logic/transform.h"
#include "../utils/vector.h"

/*  Only persp camera for now   */
typedef struct {
    vx_Position position;
    vx_Rotation rotation;

    f32 fov;
    f32 screen_rateo;
    f32 nearz;
    f32 farz;

    VX_T(f32, vx_Vec3) front;
} vx_Camera;

vx_Camera vx_camera_new(f32, f32, f32, f32);
vx_Camera vx_camera_resize_viewport(vx_Camera*, u32, u32);
#define vx_camera_new_ptr(_DEST, _FOV, _RATEO, _NEARZ, _FARZ)\
{_DEST = vx_smalloc(sizeof(vx_Camera);\
*_DEST = vx_camera_new(_FOV, _RATEO, _NEARZ, _FARZ);}

void vx_camera_move_forward(vx_Camera*, f32);
void vx_camera_move_backward(vx_Camera*, f32);
void vx_camera_move_left(vx_Camera*, f32);
void vx_camera_move_right(vx_Camera*, f32);

void vx_camera_rotate_x(vx_Camera*, f32);
void vx_camera_rotate_y(vx_Camera*, f32);
void vx_camera_rotate_z(vx_Camera*, f32);

void vx_camera_bind(vx_Camera*);

_VX_OPTION_CREATE_PROT_FOR_TYPE(vx_Camera);
_VX_VECTOR_CREATE_PROT_FOR_TYPE(vx_Camera);
