#pragma once

#define VX_CREATE_TYPE_POINTER_DEFINITION(_TYPE) typedef _TYPE* _TYPE ## _ptr

//  Merge the name of the function and the type of the template 
#define VX_TEMPLATE_NAME(_T, _NAME) _NAME ## _ ## _T
#define VX_TEMPLATE_BODY(_T, _BODY) _BODY(_T)
#define VX_TEMPLATE_PROT(_T, _PROT) _PROT(_T)
#define VX_TEMPLATE_ELEM(_T, _ELEM) _ELEM(_T)
#define VX_TEMPLATE_CALL(_T, _NAME) VX_TEMPLATE_NAME(_T, _NAME)

#define VX_TEMPLATE_NAME_1(_T, _NAME) VX_TEMPLATE_NAME(_T, _NAME)
#define VX_TEMPLATE_BODY_1(_T, _BODY) VX_TEMPLATE_BODY(_T, _BODY)
#define VX_TEMPLATE_PROT_1(_T, _PROT) VX_TEMPLATE_PROT(_T, _PROT)
#define VX_TEMPLATE_ELEM_1(_T, _ELEM) VX_TEMPLATE_ELEM(_T, _ELEM)
#define VX_TEMPLATE_CALL_1(_T, _NAME) VX_TEMPLATE_CALL(_T, _NAME)

#define VX_TEMPLATE_NAME_2(_T, _U, _NAME) _NAME ## _ ## _T ## _ ## _U
#define VX_TEMPLATE_BODY_2(_T, _U, _BODY) _BODY(_T, _U)
#define VX_TEMPLATE_PROT_2(_T, _U, _PROT) _PROT(_T, _U)
#define VX_TEMPLATE_ELEM_2(_T, _U, _ELEM) _ELEM(_T, _U)
#define VX_TEMPLATE_CALL_2(_T, _U, _NAME) VX_TEMPLATE_NAME_2(_T, _U, _NAME)

#define VX_T(_T, _EXPR) VX_TEMPLATE_NAME(_T, _EXPR)
#define VX_T_1(_T, _EXPR) VX_TEMPLATE_NAME(_T, _EXPR)
#define VX_T_2(_T, _U, _EXPR) VX_TEMPLATE_NAME_2(_T, _U, _EXPR)

/*  EXAMPLE:
*       #define T_TEST_BD(T) T VX_TEMPLATE_NAME_1(T, t_test)() {    \
*           T a = 0;                                                \
*           return a;                                               \
*       }
*       #define T_TEST_PT(T) T VX_TEMPLATE_NAME_1(T, t_test)();
*       
*       VX_TEMPLATE_PROT_1(int, T_TEST_PT);
*       VX_TEMPLATE_PROT_1(float, T_TEST_PT);
*       
*       int main() {
*           printf("\nValue Returned from t_testint(): %d\nValue Returned from t_testfloat(): %f\n", VX_TEMPLATE_CALL_1(int, t_test)(), VX_TEMPLATE_CALL_1(float, t_test)());
*       
*           return 0;
*       }
*       
*       VX_TEMPLATE_BODY_1(int, T_TEST_BD);
*       VX_TEMPLATE_BODY_1(float, T_TEST_BD);
*/
