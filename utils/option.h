#pragma once
#include "template.h"
#include "types.h"
#include <stdbool.h>
#include "panic.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
#define _VX_OPTION_ELEM(T) typedef struct {                                                         \
    bool is_some;                                                                                   \
    T data;                                                                                         \
} VX_TEMPLATE_NAME(T, vx_Option);
#define _VX_OPTION_SOME_PT(T) VX_TEMPLATE_NAME(T, vx_Option) VX_TEMPLATE_NAME(T, vx_option_some)(T);
#define _VX_OPTION_SOME_BD(T) VX_TEMPLATE_NAME(T, vx_Option) VX_TEMPLATE_NAME(T, vx_option_some)(T value) {\
    VX_TEMPLATE_NAME(T, vx_Option) option;                                                          \
    option.is_some = true;                                                                          \
    option.data = value;                                                                            \
    return option;                                                                                  \
}
#define _VX_OPTION_NONE_PT(T) VX_TEMPLATE_NAME(T, vx_Option) VX_TEMPLATE_NAME(T, vx_option_none)();
#define _VX_OPTION_NONE_BD(T) VX_TEMPLATE_NAME(T, vx_Option) VX_TEMPLATE_NAME(T, vx_option_none)() {\
    VX_TEMPLATE_NAME(T, vx_Option) option;                                                          \
    option.is_some = false;                                                                         \
    return option;                                                                                  \
}
#define _VX_OPTION_UNWRAP_PT(T) T VX_TEMPLATE_NAME(T, vx_option_unwrap)(VX_TEMPLATE_NAME(T, vx_Option));
#define _VX_OPTION_UNWRAP_BD(T) T VX_TEMPLATE_NAME(T, vx_option_unwrap)(VX_TEMPLATE_NAME(T, vx_Option) option) {\
    VX_ASSERT("None value found when unwrapping option!", option.is_some);                          \
    return option.data;                                                                             \
}

#define _VX_OPTION_CREATE_PROT_FOR_TYPE(_T) VX_TEMPLATE_ELEM(_T, _VX_OPTION_ELEM)                   \
VX_TEMPLATE_PROT(_T, _VX_OPTION_SOME_PT)                                                            \
VX_TEMPLATE_PROT(_T, _VX_OPTION_NONE_PT)                                                            \
VX_TEMPLATE_PROT(_T, _VX_OPTION_UNWRAP_PT)
#define _VX_OPTION_CREATE_BODY_FOR_TYPE(_T) VX_TEMPLATE_BODY(_T, _VX_OPTION_SOME_BD)                \
VX_TEMPLATE_BODY(_T, _VX_OPTION_NONE_BD)                                                            \
VX_TEMPLATE_BODY(_T, _VX_OPTION_UNWRAP_BD)

///////////////////////////////////////////////////////////////////////////////////////////////////
// MAY BE BROKEN!!! DO NOT USE!
/*#define _VX_RESULT_ELEM(T, U) typedef struct {                                                    \
    bool is_some;                                                                                   \
    union {                                                                                         \
        T ok;                                                                                       \
        U err;                                                                                      \
    };                                                                                              \
} VX_TEMPLATE_NAME_2(T, U, vx_Result);
#define _VX_RESULT_SOME_PT(T, U) VX_TEMPLATE_NAME_2(T, U, vx_Result) VX_TEMPLATE_NAME_2(T, U, vx_result_some)(T);
#define _VX_RESULT_SOME_BD(T, U) VX_TEMPLATE_NAME_2(T, U, vx_Result) VX_TEMPLATE_NAME_2(T, U, vx_result_some)(T value) {\
    VX_TEMPLATE_NAME_2(T, U, vx_Result) result;                                                     \
    result.is_some = true;                                                                          \
    result.ok = value;                                                                              \
    return result;                                                                                  \
}
#define _VX_RESULT_NONE_PT(T, U) VX_TEMPLATE_NAME_2(T, U, vx_Result) VX_TEMPLATE_NAME_2(T, U, vx_result_none)(U);
#define _VX_RESULT_NONE_BD(T, U) VX_TEMPLATE_NAME_2(T, U, vx_Result) VX_TEMPLATE_NAME_2(T, U, vx_result_none)(U value) {\
    VX_TEMPLATE_NAME_2(T, U, vx_Result) result;                                                     \
    result.is_some = false;                                                                         \
    result.err = value;                                                                             \
}
#define _VX_RESULT_UNWRAP_PT(T, U) T VX_TEMPLATE_NAME_2(T, U, vx_result_unwrap)(VX_TEMPLATE_NAME_2(T, U, vx_Result));
#define _VX_RESULT_UNWRAP_BD(T, U) T VX_TEMPLATE_NAME_2(T, U, vx_result_unwrap)(VX_TEMPLATE_NAME_2(T, U, vx_Result) result) {\
    if (!result.is_some) {                                                                          \
        assert(0);                                                                                  \
    }                                                                                               \
    return result.ok;                                                                               \
}

#define _VX_RESULT_CREATE_PROT_FOR_TYPE(_T, _U) VX_TEMPLATE_ELEM_2(_T, _U, _VX_RESULT_ELEM)         \
VX_TEMPLATE_PROT_2(_T, _U, _VX_RESULT_SOME_PT)                                                      \
VX_TEMPLATE_PROT_2(_T, _U, _VX_RESULT_NONE_PT)                                                      \
VX_TEMPLATE_PROT_2(_T, _U, _VX_RESULT_UNWRAP_PT)
#define _VX_RESULT_CREATE_BODY_FOR_TYPE(_T, _U) VX_TEMPLATE_BODY_2(_T, _U, _VX_RESULT_SOME_BD)      \
VX_TEMPLATE_BODY_2(_T, _U, _VX_RESULT_NONE_BD)                                                      \
VX_TEMPLATE_BODY_2(_T, _U, _VX_RESULT_UNWRAP_BD)*/

///////////////////////////////////////////////////////////////////////////////////////////////////
_VX_OPTION_CREATE_PROT_FOR_TYPE(u8)
_VX_OPTION_CREATE_PROT_FOR_TYPE(u16)
_VX_OPTION_CREATE_PROT_FOR_TYPE(u32)
_VX_OPTION_CREATE_PROT_FOR_TYPE(u64)
_VX_OPTION_CREATE_PROT_FOR_TYPE(i8)
_VX_OPTION_CREATE_PROT_FOR_TYPE(i16)
_VX_OPTION_CREATE_PROT_FOR_TYPE(i32)
_VX_OPTION_CREATE_PROT_FOR_TYPE(i64)
_VX_OPTION_CREATE_PROT_FOR_TYPE(f32)
_VX_OPTION_CREATE_PROT_FOR_TYPE(f64)

///////////////////////////////////////////////////////////////////////////////////////////////////
/*  vx_Option example:
*       #include <stdio.h>
*       #include <enums.h>
*       #include <math.h>
*       
*       //  If the number is negative we do not return anything
*       vx_Option_float safe_sqrt(float n) {
*           if (n < 0) {
*               return vx_option_none_float();
*           }
*       
*           return vx_option_some_float(sqrtf(n));
*       }
*       
*       int main() {
*           printf("%f", vx_option_unwrap_float(safe_sqrt(-40)));
*       
*           return 0;
*       }
*/
