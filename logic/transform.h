#pragma once
#include "../utils/types.h"
#include "../utils/default.h"
#include "vec.h"

typedef VX_T(f32, vx_Vec3) vx_Position;
VX_CREATE_DEFAULT(vx_Position, .x = 0, .y = 0, .z = 0)
#define VX_POSITION_NEW(_X, _Y, _Z) VX_VEC3_NEW(f32, _X, _Y, _Z)

typedef VX_T(f32, vx_Vec3) vx_Rotation;
VX_CREATE_DEFAULT(vx_Rotation, .x = 0, .y = 0, .z = 0)
#define VX_ROTATION_NEW(_X, _Y, _Z) VX_VEC3_NEW(f32, _X, _Y, _Z)

typedef VX_T(f32, vx_Vec3) vx_Scale;
VX_CREATE_DEFAULT(vx_Scale, .x = 0, .y = 0, .z = 0)
#define VX_SCALE_NEW(_X, _Y, _Z) VX_VEC3_NEW(f32, _X, _Y, _Z)
