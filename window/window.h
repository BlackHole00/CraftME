#pragma once
#include <windows.h>
#include "../gfx/renderer.h"
#include "../utils/types.h"
#include "../utils/dummy_func.h"
#include "../logic/vec.h"

#define VX_KEY_JUST_PRESSED 0x01

typedef struct vx_Window {
    WNDCLASS wc;
    HWND hwnd;
    HDC hdc;
    HGLRC hrc;
    bool should_close;

    bool grab_cursor;
    VX_T(i32, vx_Vec2) mouse_offset;

    bool fullscreen;

    void* user_state;
    void (*init)(void*, void*, vx_Renderer*);
    void (*logic)(void*, void*, f32, vx_Renderer*);
    void (*draw)(void*, vx_Renderer*);
    void (*close)(void*, void*, vx_Renderer*);

    vx_Renderer* renderer;
} vx_Window;

vx_Window vx_window_new(HINSTANCE, char*, usize, usize, bool);
vx_Window vx_window_from_wndclass(HINSTANCE, WNDCLASS, char*, usize, usize, bool);
void vx_Window_run(vx_Window*, void*);
