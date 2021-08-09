#include "window.h"
#include "../utils/panic.h"
#include <time.h>

static LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
                          WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        return 0;
    case WM_CLOSE:
        PostQuitMessage (0);
        return 0;

    case WM_DESTROY:
        return 0;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            return 0;
        }
        return 0;

    default:
        return DefWindowProc (hWnd, message, wParam, lParam);
    }
}

static void change_to_fullscreen(i32 width, i32 height)
{
	DEVMODE dmSettings;									// Device Mode variable - Needed to change modes

	memset(&dmSettings,0,sizeof(dmSettings));			// Makes Sure Memory's Cleared

	// Get the current display settings.  This function fills our the settings.
	VX_ASSERT("Could Not Enum Display Settings", EnumDisplaySettings(NULL,ENUM_CURRENT_SETTINGS,&dmSettings));

	dmSettings.dmPelsWidth	= width;					// Set the desired Screen Width
	dmSettings.dmPelsHeight	= height;					// Set the desired Screen Height
	dmSettings.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;	// Set the flags saying we're changing the Screen Width and Height
	
	// This function actually changes the screen to full screen
	// CDS_FULLSCREEN Gets Rid Of Start Bar.
	// We always want to get a result from this function to check if we failed
	int result = ChangeDisplaySettings(&dmSettings, CDS_FULLSCREEN);	

	// Check if we didn't receive a good return message From the function
	VX_ASSERT("Display Mode Not Compatible", ChangeDisplaySettings(&dmSettings, CDS_FULLSCREEN) == DISP_CHANGE_SUCCESSFUL);
}

static void enable_opengl (HWND hWnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC (hWnd);

    /* set the pixel format for the DC */
    ZeroMemory (&pfd, sizeof (pfd));
    pfd.nSize = sizeof (pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
      PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat (*hDC, &pfd);
    SetPixelFormat (*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext( *hDC );
    wglMakeCurrent( *hDC, *hRC );

}

static void disable_opengl (HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}


vx_Window vx_window_new(HINSTANCE hinstance, char* window_name, usize width, usize heigth, bool fullscreen) {
    WNDCLASS wc;

    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hinstance;
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = window_name;
    RegisterClass (&wc);

    return vx_window_from_wndclass(hinstance, wc, window_name, width, heigth, fullscreen);
}

vx_Window vx_window_from_wndclass(HINSTANCE hinstance, WNDCLASS wc, char* window_name, usize width, usize heigth, bool fullscreen) {
    vx_Window window;
    window.init = NULL;
    window.draw = NULL;
    window.logic = NULL;
    window.close = NULL;

    window.renderer = NULL;

    window.should_close = false;
    window.grab_cursor = true;
    window.mouse_offset = VX_VEC2_NEW(i32, 0, 0);
    window.fullscreen = fullscreen;

    if (fullscreen) {
        change_to_fullscreen(width, heigth);
    }

    window.wc = wc;
    window.hwnd = CreateWindow (
        window_name, window_name,
        (fullscreen ? (WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE) : (WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE)),
        0, 0, width, heigth,
        NULL, NULL, hinstance, NULL
    );

    enable_opengl(window.hwnd, &window.hdc, &window.hrc);
    UpdateWindow (window.hwnd);

    return window;
}

void vx_Window_run(vx_Window* window, void* user_state) {
    MSG msg;
    clock_t old;
    clock_t now = clock();

    // convert to safe functions
    window->init    = VX_SAFE_FUNC_PTR(window->init);
    window->logic   = VX_SAFE_FUNC_PTR(window->logic);
    window->draw    = VX_SAFE_FUNC_PTR(window->draw);
    window->close   = VX_SAFE_FUNC_PTR(window->close);
    
    if (window->renderer == NULL) {
        window->renderer = vx_smalloc(sizeof(vx_Renderer));
        *window->renderer = vx_renderer_new();
    }

    window->user_state = user_state;

    window->init(window, window->user_state, window->renderer);

    while (!window->should_close) {
        /* check for messages */
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE)) {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT) {
                window->should_close = TRUE;
            }
            else {
                TranslateMessage (&msg);
                DispatchMessage (&msg);
            }
        }
        else {
            if (window->grab_cursor) {
                POINT cursor_pos;
                GetCursorPos(&cursor_pos);

                RECT window_rect;
                GetWindowRect(window->hwnd, &window_rect);

                u32 window_width = window_rect.right - window_rect.left;
                u32 window_heigth = window_rect.bottom - window_rect.top;

                u32 opt_cursor_pos_x = window_rect.left + (window_width / 2);
                u32 opt_cursor_pos_y = window_rect.top + (window_heigth / 2);

                window->mouse_offset.x = cursor_pos.x - opt_cursor_pos_x;
                /*  Windows Y coords are inverted.  */
                window->mouse_offset.y = opt_cursor_pos_y - cursor_pos.y;

                SetCursorPos(opt_cursor_pos_x, opt_cursor_pos_y);
            } else {
                window->mouse_offset = VX_VEC2_NEW(i32, 0, 0);
            }

            old = now;
            now = clock();
            f32 delta = (f32)(now - old) / 100.0f;
            /*if (delta <= 0.01) { delta = 0.01; }*/

            window->logic(window, window->user_state, delta, window->renderer);
            vx_renderer_clearscr(window->renderer);
            vx_renderer_draw_preparation(window->renderer);
            window->draw(window->user_state, window->renderer);

            SwapBuffers (window->hdc);
            Sleep (1);
        }
    }

    if (window->fullscreen) {
        change_to_fullscreen(640, 480);
        ChangeDisplaySettings(NULL, 0);
    }
    window->close(window, window->user_state, window->renderer);
    vx_renderer_free(window->renderer);
    free(window->renderer);
    disable_opengl(window->hwnd, window->hdc, window->hrc);
}
