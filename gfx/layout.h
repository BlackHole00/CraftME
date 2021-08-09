#pragma once
#include "../utils/types.h"
#include "../utils/vector.h"

/*  Similar to the modern OpenGL n, it is used to tell the program how to read buffer data.
*/
typedef enum {
    VX_POSITION_2F32 = 0,
    VX_POSITION_3F32 = 1,
    VX_COLOR_3F32 = 2,
    VX_COLOR_4F32 = 3,
    VX_UV_2F32 = 4,
/* TODO (#1#): Add all types... */
} vx_LayoutElement;

VX_TEMPLATE_PROT(vx_LayoutElement, _VX_VECTOR_PUSH_PT);

typedef VX_VECTOR(vx_LayoutElement) vx_Layout;

#define vx_layout_new() vx_vector_new()
#define vx_layout_free(_LAY) vx_vector_free(_LAY)
#define vx_layout_push(_LAY, _ELEM) VX_T(vx_LayoutElement, vx_vector_push)(_LAY, _ELEM)
#define vx_layout_clear(_LAY) vx_layout_clear(_LAY)
#define VX_LAYOUT_DATA(_LAY) ((vx_LayoutElement*)((_LAY)->data))

