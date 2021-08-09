/**************************
 * Includes
 *
 **************************/
#include <stdio.h>
#include <windows.h>
#include <gl/glu.h>
#include "utils/utils.h"
#include "gfx/gfx.h"
#include "window/window.h"
#include "game/game.h"
#include <stdlib.h>
#include <time.h>

const u32 WIDTH = 1920;
const u32 HEIGTH = 1080;

/**************************
 * Function Declarations
 *
 **************************/

void process_camera_input(vx_Camera*, VX_T(i32, vx_Vec2), f32);

typedef struct {
    gm_World world;
} State;

void init(vx_Window* window, State* state, vx_Renderer* renderer) {
    ShowCursor(false);

    srand(time(NULL));

    VX_DEFAULT(vx_Position);

    /*  The renderer has a default camera, but it's suggested to push a new camera  */
    vx_Camera camera = vx_camera_new(120.0f, WIDTH / (f32)HEIGTH, 0.1f, 250.0f);
    camera.position = VX_POSITION_NEW(25.0f, 20.0f, 25.0f);
    vx_renderer_push_camera(renderer, camera);

    glViewport(0, 0, WIDTH, HEIGTH);

    /*  Set renderer flags  */
    vx_renderer_set_cull(renderer, true);
    vx_renderer_set_depth_test(renderer, true);
    renderer->flags.clear_color = VX_VEC4_NEW(f32, 0.2f, 0.7f, 0.9f, 1.0f);

    /*  Create a new world and register the standard blocks, then generate the world */
    state->world = gm_world_new(10);

    gm_block_manager_push_standard_color_blocks(&(state->world.block_manager));

    gm_world_gen_chunks(&state->world);
    gm_world_gen_all_meshes(&state->world);
}

void logic(vx_Window* window, State* state, f32 delta, vx_Renderer* renderer) {
    /*  The renderer has a default camera. We don't need to push one... */
    process_camera_input(vx_renderer_get_current_camera(renderer), window->mouse_offset, delta);

    if (GetAsyncKeyState(VK_TAB) & VX_KEY_JUST_PRESSED){
        window->grab_cursor = !window->grab_cursor;
        ShowCursor(!window->grab_cursor);
    }

    /*  Debug keys just for fun!    */
    if (GetAsyncKeyState('Z') & VX_KEY_JUST_PRESSED){
        vx_renderer_set_wireframe(renderer, !renderer->flags.wireframe);
    }
    if (GetAsyncKeyState('X')) {
        (state->world.chunks[GM_WORLD_POS_TO_INDEX(state->world.render_distance, 2, 2, 2)].blocks)[7][7][7] = 1;
        gm_world_regen_chunk_mesh(&state->world, 2, 2, 2);
    }
}

void draw(State* state, vx_Renderer* renderer) {
    gm_world_draw(&state->world);

    GL_CHECK_ERRORS();
}

void close(vx_Window* window, State* state, vx_Renderer* renderer) {
    gm_world_free(&state->world);

    ShowCursor(true);
}

void process_camera_input(vx_Camera* camera, VX_T(i32, vx_Vec2) mouse_offset, f32 delta) {
    /*  LOOK    */
    if (GetAsyncKeyState(VK_LEFT)) {
        vx_camera_rotate_x(camera, -5.0f * delta);
    } else if (GetAsyncKeyState(VK_RIGHT)) {
        vx_camera_rotate_x(camera, 5.0f * delta);
    }
    if (GetAsyncKeyState(VK_DOWN)) {
        vx_camera_rotate_y(camera, 5.0f * delta);
    } else if (GetAsyncKeyState(VK_UP)) {
        vx_camera_rotate_y(camera, -5.0f * delta);
    }

    if (GetAsyncKeyState('R')) {
        camera->fov += 1.0f * delta;
    } else if (GetAsyncKeyState('T')) {
        camera->fov -= 1.0f * delta;
    }

    /*  MOUSE LOOK  */
    vx_camera_rotate_x(camera, mouse_offset.x / 2.5f);
    vx_camera_rotate_y(camera, mouse_offset.y / 2.5f);

    /*  MOVEMENT    */
    if (GetAsyncKeyState('W')) {
        vx_camera_move_forward(camera, 0.5f * delta);
    } else if (GetAsyncKeyState('S')) {
        vx_camera_move_backward(camera, 0.5f * delta);
    }
    if (GetAsyncKeyState('D')) {
        vx_camera_move_right(camera, 0.5f * delta);
    } else if (GetAsyncKeyState('A')) {
        vx_camera_move_left(camera, 0.5f * delta);
    }

    if (GetAsyncKeyState(VK_SPACE)) {
        camera->position.y += 0.5f * delta;
    } else if (GetAsyncKeyState(VK_CONTROL)) {
        camera->position.y -= 0.5f * delta;
    }
}

/**************************
 * WinMain
 *
 **************************/

int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int iCmdShow)
{
    freopen("log.txt", "w", stdout);

    vx_Window window    = vx_window_new(hInstance, "OpenGL", WIDTH, HEIGTH, true);
    window.init         = init;
    window.logic        = logic;
    window.draw         = draw;
    window.close        = close;

    State state;
    vx_Window_run(&window, &state);
}
