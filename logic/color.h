#pragma once
#include "vec.h"
#include "../utils/default.h"

typedef struct {
    f32 r;
    f32 g;
    f32 b;
    f32 a;
} vx_Color4;

#define VX_COLOR4_NEW(_R, _G, _B, _A) (vx_Color4){ .r = _R, .g = _G, .b = _B, .a = _A }
#define VX_COLOR4_FROM_VEC4(_VEC4) (vx_Color4)(_VEC4)
VX_CREATE_DEFAULT(vx_Color4, .r = 1.0f, .g = 1.0f, .b = 1.0f, .a = 1.0f)


typedef struct {
    f32 r;
    f32 g;
    f32 b;
} vx_Color3;

#define VX_COLOR3_NEW(_R, _G, _B) (vx_Color3){ .r = _R, .g = _G, .b = _B }
#define VX_COLOR3_FROM_VEC3(_VEC3) (vx_Color3)(_VEC3)
VX_CREATE_DEFAULT(vx_Color3, .r = 1.0f, .g = 1.0f, .b = 1.0f)
