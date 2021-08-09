#include "vector.h"
#include <stdio.h>

vx_Vector vx_vector_new() {
    vx_Vector self;

    self.data = vx_smalloc(0);
    self.length = 0;
    self.mem_length = 0;

    return self;
}

void vx_vector_free(vx_Vector* self) {
    free(self->data);
}

void vx_vector_clear(vx_Vector* self) {
    self->data = vx_srealloc(self->data, 0);                                                        \
    self->length = 0;                                                                               \
    self->mem_length = 0; 
}

_VX_VECTOR_CREATE_BODY_FOR_TYPE(u8)
_VX_VECTOR_CREATE_BODY_FOR_TYPE(u16)
_VX_VECTOR_CREATE_BODY_FOR_TYPE(u32)
_VX_VECTOR_CREATE_BODY_FOR_TYPE(u64)
_VX_VECTOR_CREATE_BODY_FOR_TYPE(i8)
_VX_VECTOR_CREATE_BODY_FOR_TYPE(i16)
_VX_VECTOR_CREATE_BODY_FOR_TYPE(i32)
_VX_VECTOR_CREATE_BODY_FOR_TYPE(i64)
_VX_VECTOR_CREATE_BODY_FOR_TYPE(f32)
_VX_VECTOR_CREATE_BODY_FOR_TYPE(f64)
