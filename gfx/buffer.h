#pragma once
#include "../utils/types.h"
#include "../utils/vector.h"
#include "layout.h"
#include <gl/gl.h>

typedef struct {
    vx_LayoutElement elem;
    u32 start_data; /*  When we should start to use this hint   */
} vx_BufferHintLayoutElement;
_VX_OPTION_CREATE_PROT_FOR_TYPE(vx_BufferHintLayoutElement)
_VX_VECTOR_CREATE_PROT_FOR_TYPE(vx_BufferHintLayoutElement)

/*  OpenGL 1.x only allow floats or doubles vertex data.
*   We do not need a buffer of bytes (or anything smaller than floats). 
*   We only need a buffer of floats.
*   Currently doubles are not supported. They are not that usefull...
*/
typedef struct {
    VX_VECTOR(f32) data;
    VX_VECTOR(f32) hints;
    VX_VECTOR(vx_BufferHintLayoutElement) hints_layout;
} vx_Buffer;

vx_Buffer vx_buffer_new();

void vx_buffer_free(vx_Buffer*);
void vx_buffer_clear(vx_Buffer*);

#define VX_BUFFER_DATA(_BUF_PTR) VX_VECTOR_DATA(f32, &(_BUF_PTR->data))
#define VX_BUFFER_HINTS_DATA(_BUF_PTR) VX_VECTOR_DATA(f32, &(_BUF_PTR->hints))

#define vx_buffer_push(_BUF_PTR, _VAL) VX_T(f32, vx_vector_push)(&(_BUF_PTR->data), _VAL)
void vx_buffer_push_2(vx_Buffer*, f32, f32);
void vx_buffer_push_3(vx_Buffer*, f32, f32, f32);
void vx_buffer_push_4(vx_Buffer*, f32, f32, f32, f32);

#define vx_buffer_hint_layout_raw(_BUF_PTR, _VAL) VX_T(vx_BufferHintLayoutElement, vx_vector_push)(&(_BUF_PTR->hints_layout), _VAL)
#define vx_buffer_hint_raw(_BUF_PTR, _VAL) VX_T(f32, vx_vector_push)(&(_BUF_PTR->hints), _VAL)
void vx_buffer_hint_color3(vx_Buffer*, f32, f32, f32);
void vx_buffer_hint_color4(vx_Buffer*, f32, f32, f32, f32);
/* TODO (#1#): Finish and add normals, texture... */

void vx_buffer_draw(vx_Buffer*, vx_Layout*, GLenum);
