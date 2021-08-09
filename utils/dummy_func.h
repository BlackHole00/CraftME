#pragma once
void _vx_dummy_func();

#define VX_SAFE_FUNC_PTR(_PTR) ((void*)_PTR == NULL ? _vx_dummy_func : _PTR)
