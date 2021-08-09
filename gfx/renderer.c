#include "renderer.h"
#include <gl/gl.h>

vx_Renderer vx_renderer_new() {
    vx_Renderer renderer;
    renderer.camera_stack = vx_vector_new();
    renderer.flags.wireframe = false;
    renderer.flags.cull = false;
    renderer.flags.depth_test = true;
    renderer.flags.clear = true;
    renderer.flags.clear_color = VX_VEC4_NEW(f32, 0.0f, 0.0f, 0.0f, 0.0f);

    /*  Push a default camera   */
    vx_renderer_push_new_camera(&renderer);

    return renderer;
}

void vx_renderer_free(vx_Renderer* renderer) {
    vx_vector_free(&(renderer->camera_stack));
}

void vx_renderer_clearscr(vx_Renderer* renderer) {
    if (renderer->should_update_flags) {
        glPolygonMode(GL_FRONT_AND_BACK, renderer->flags.wireframe ? GL_LINE : GL_FILL);

        if (renderer->flags.depth_test) {
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);
        } else {
            glDisable(GL_DEPTH_TEST);
        }

        if (renderer->flags.cull) {
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
            glFrontFace(GL_CW);
        } else {
            glDisable(GL_CULL_FACE);
        }
    }

    glClearColor(renderer->flags.clear_color.x, renderer->flags.clear_color.y, renderer->flags.clear_color.z, renderer->flags.clear_color.w);
    u32 flags = 0;
    flags |= (renderer->flags.clear ? GL_COLOR_BUFFER_BIT : 0);
    flags |= (renderer->flags.depth_test ? GL_DEPTH_BUFFER_BIT : 0 /*GL_DEPTH_BUFFER_BIT*/);
    glClear(flags);
}

void vx_renderer_set_wireframe(vx_Renderer* renderer, bool value) {
    renderer->should_update_flags = true;
    renderer->flags.wireframe = value;
}

void vx_renderer_set_cull(vx_Renderer* renderer, bool value) {
    renderer->should_update_flags = true;
    renderer->flags.cull = value;
}

void vx_renderer_set_depth_test(vx_Renderer* renderer, bool value) {
    renderer->should_update_flags = true;
    renderer->flags.depth_test = value;
}

void vx_renderer_set_clear(vx_Renderer* renderer, bool value) {
    renderer->should_update_flags = true;
    renderer->flags.clear = value;
}

void vx_renderer_draw_preparation(vx_Renderer* renderer) {
    vx_camera_bind(vx_renderer_get_current_camera(renderer));
}

void vx_renderer_push_camera(vx_Renderer* renderer, vx_Camera camera) {
    VX_T(vx_Camera, vx_vector_push)(&(renderer->camera_stack), camera);

    renderer->should_update_camera = true;
}

void vx_renderer_push_new_camera(vx_Renderer* renderer) {
    vx_Camera camera = vx_camera_new(90.0f, 1.0f, 0.01f, 100.0f);
    camera.position = VX_POSITION_NEW(0.0f, 0.0f, -1.0f);
    camera.rotation = VX_ROTATION_NEW(0.0f, 0.0f, 0.0f);
    vx_renderer_push_camera(renderer, camera);
}

vx_Camera* vx_renderer_get_current_camera(vx_Renderer* renderer) {
    if (renderer->camera_stack.length <= 0) {
        VX_PANIC("No cameras found in renderer!");
    }

    return (&(VX_VECTOR_DATA(vx_Camera, &(renderer->camera_stack))[renderer->camera_stack.length - 1]));
}

VX_T(vx_Camera, vx_Option) vx_renderer_pop_camera(vx_Renderer* renderer) {
    VX_T(vx_Camera, vx_Option) res = VX_T(vx_Camera, vx_vector_pop)(&(renderer->camera_stack));

    renderer->should_update_camera = true;

    return res;
}

