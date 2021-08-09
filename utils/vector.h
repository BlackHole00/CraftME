#pragma once
#include <malloc.h>
#include "types.h"
#include "template.h"
#include "option.h"
#include "mem.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct {
    void* data;
    usize length;
    usize mem_length;
} vx_Vector;

///////////////////////////////////////////////////////////////////////////////////////////////////
#define VX_VECTOR(_T) vx_Vector
#define VX_VECTOR_DATA(_T, _VEC) ((_T*)((_VEC)->data))
#define _VX_VECTOR_PUSH_PT(T) void VX_TEMPLATE_NAME(T, vx_vector_push)(vx_Vector*, T);
#define _VX_VECTOR_PUSH_BD(T) void VX_TEMPLATE_NAME(T, vx_vector_push)(vx_Vector* self, T value) {  \
    /* If the vector is full, then enlarge it.*/                                                    \
    if (self->length >= self->mem_length) {                                                         \
        self->mem_length = (self->mem_length == 0) ? 1 : self->mem_length * 2;                      \
        self->data = vx_srealloc(self->data, self->mem_length * sizeof(T));                         \
    }                                                                                               \
                                                                                                    \
    /* Push the new value*/                                                                         \
    VX_VECTOR_DATA(T, self)[self->length] = value;                                                  \
    self->length++;                                                                                 \
}
#define _VX_VECTOR_POP_PT(T) VX_TEMPLATE_NAME(T, vx_Option) VX_TEMPLATE_NAME(T, vx_vector_pop)(vx_Vector*);
#define _VX_VECTOR_POP_BD(T) VX_TEMPLATE_NAME(T, vx_Option) VX_TEMPLATE_NAME(T, vx_vector_pop)(vx_Vector* self) {\
    if (self->length > 0) {                                                                         \
        T top = VX_VECTOR_DATA(T, self)[self->length - 1];                                          \
        self->length--;                                                                             \
                                                                                                    \
        if (self->length <= (self->mem_length / 2)) {                                               \
            self->mem_length = self->mem_length / 2;                                                \
            self->data = vx_srealloc(self->data, self->mem_length * sizeof(T));                     \
        }                                                                                           \
        return VX_TEMPLATE_CALL(T, vx_option_some)(top);                                            \
    }                                                                                               \
    return VX_TEMPLATE_CALL(T, vx_option_none)();                                                   \
}
#define _VX_VECTOR_TOP_PT(T) VX_TEMPLATE_NAME(T, vx_Option) VX_TEMPLATE_NAME(T, vx_vector_top)(vx_Vector*);
#define _VX_VECTOR_TOP_BD(T) VX_TEMPLATE_NAME(T, vx_Option) VX_TEMPLATE_NAME(T, vx_vector_top)(vx_Vector* self) {\
    if (self->length > 0) {                                                                         \
        return VX_TEMPLATE_CALL(T, vx_option_some)(VX_VECTOR_DATA(T, self)[self->length - 1]);      \
    }                                                                                               \
    return VX_TEMPLATE_CALL(T, vx_option_none)();                                                   \
}
#define _VX_VECTOR_GET_PT(T) VX_TEMPLATE_NAME(T, vx_Option) VX_TEMPLATE_NAME(T, vx_vector_get)(vx_Vector*, u32);
#define _VX_VECTOR_GET_BD(T) VX_TEMPLATE_NAME(T, vx_Option) VX_TEMPLATE_NAME(T, vx_vector_get)(vx_Vector* self, u32 index) {\
    if (index < self->length) {                                                                     \
        return VX_TEMPLATE_CALL(T, vx_option_some)(VX_VECTOR_DATA(T, self)[index]);                 \
    }                                                                                               \
    return VX_TEMPLATE_CALL(T, vx_option_none)();                                                   \
}

#define _VX_VECTOR_CREATE_PROT_FOR_TYPE(_T) VX_TEMPLATE_PROT(_T, _VX_VECTOR_PUSH_PT)                \
VX_TEMPLATE_PROT(_T, _VX_VECTOR_POP_PT)                                                             \
VX_TEMPLATE_PROT(_T, _VX_VECTOR_TOP_PT)                                                             \
VX_TEMPLATE_PROT(_T, _VX_VECTOR_GET_PT)
#define _VX_VECTOR_CREATE_BODY_FOR_TYPE(_T) VX_TEMPLATE_BODY(_T, _VX_VECTOR_PUSH_BD)                \
VX_TEMPLATE_BODY(_T, _VX_VECTOR_POP_BD)                                                             \
VX_TEMPLATE_BODY(_T, _VX_VECTOR_TOP_BD)                                                             \
VX_TEMPLATE_BODY(_T, _VX_VECTOR_GET_BD)

///////////////////////////////////////////////////////////////////////////////////////////////////
vx_Vector vx_vector_new();
void vx_vector_free(vx_Vector*);
void vx_vector_clear(vx_Vector*);

_VX_VECTOR_CREATE_PROT_FOR_TYPE(u8)
_VX_VECTOR_CREATE_PROT_FOR_TYPE(u16)
_VX_VECTOR_CREATE_PROT_FOR_TYPE(u32)
_VX_VECTOR_CREATE_PROT_FOR_TYPE(u64)
_VX_VECTOR_CREATE_PROT_FOR_TYPE(i8)
_VX_VECTOR_CREATE_PROT_FOR_TYPE(i16)
_VX_VECTOR_CREATE_PROT_FOR_TYPE(i32)
_VX_VECTOR_CREATE_PROT_FOR_TYPE(i64)
_VX_VECTOR_CREATE_PROT_FOR_TYPE(f32)
_VX_VECTOR_CREATE_PROT_FOR_TYPE(f64)
