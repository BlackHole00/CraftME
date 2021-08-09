#pragma once
#include "../utils/types.h"
#include "../utils/template.h"

#define _VX_VEC2_ELEM(T) typedef struct {\
    T x;\
    T y;\
} VX_TEMPLATE_NAME(T, vx_Vec2);
#define VX_VEC2_NEW(_T, _X, _Y) (VX_TEMPLATE_NAME(_T, vx_Vec2)){.x = _X, .y = _Y}

#define _VX_VEC3_ELEM(T) typedef struct {\
    T x;\
    T y;\
    T z;\
} VX_TEMPLATE_NAME(T, vx_Vec3);
#define VX_VEC3_NEW(_T, _X, _Y, _Z) (VX_TEMPLATE_NAME(_T, vx_Vec3)){.x = _X, .y = _Y, .z = _Z}

#define _VX_VEC4_ELEM(T) typedef struct {\
    T x;\
    T y;\
    T z;\
    T w;\
} VX_TEMPLATE_NAME(T, vx_Vec4);
#define VX_VEC4_NEW(_T, _X, _Y, _Z, _W) (VX_TEMPLATE_NAME(_T, vx_Vec4)){.x = _X, .y = _Y, .z = _Z, .w = _W}

#define _VX_VEC_CREATE_ELEMS_FOR_TYPE(_T) VX_TEMPLATE_ELEM(_T, _VX_VEC2_ELEM)\
VX_TEMPLATE_ELEM(_T, _VX_VEC3_ELEM)\
VX_TEMPLATE_ELEM(_T, _VX_VEC4_ELEM)

_VX_VEC_CREATE_ELEMS_FOR_TYPE(u8)
_VX_VEC_CREATE_ELEMS_FOR_TYPE(u16)
_VX_VEC_CREATE_ELEMS_FOR_TYPE(u32)
_VX_VEC_CREATE_ELEMS_FOR_TYPE(u64)
_VX_VEC_CREATE_ELEMS_FOR_TYPE(i8)
_VX_VEC_CREATE_ELEMS_FOR_TYPE(i16)
_VX_VEC_CREATE_ELEMS_FOR_TYPE(i32)
_VX_VEC_CREATE_ELEMS_FOR_TYPE(i64)
_VX_VEC_CREATE_ELEMS_FOR_TYPE(f32)
_VX_VEC_CREATE_ELEMS_FOR_TYPE(f64)
