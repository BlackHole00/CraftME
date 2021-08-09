#include "camera.h"
#include "gl/gl.h"
#include "gl/glu.h"
#include "../utils/math.h"
#include <math.h>

static void update_front(vx_Camera* camera) {
    camera->front.x = cos(vx_deg_to_rad(camera->rotation.x)) * cos(vx_deg_to_rad(camera->rotation.y));
    camera->front.y = sin(vx_deg_to_rad(camera->rotation.y));
    camera->front.z = sin(vx_deg_to_rad(camera->rotation.x)) * cos(vx_deg_to_rad(camera->rotation.y));
}

vx_Camera vx_camera_new(f32 fov, f32 screen_rateo, f32 nearz, f32 farz) {
    vx_Camera camera;
    camera.fov          = fov;
    camera.screen_rateo = screen_rateo;
    camera.nearz        = nearz;
    camera.farz         = farz;
    
    camera.position = VX_POSITION_NEW(0.0f, 0.0f, 0.0f);
    camera.rotation = VX_ROTATION_NEW(0.0f, 0.0f, 0.0f);
    camera.front    = VX_VEC3_NEW(f32, 0.0f, 0.0f, 0.0f);

    return camera;
}

vx_Camera vx_camera_resize_viewport(vx_Camera* camera, u32 width, u32 heigth) {
    glViewport(0.0, 0.0, (f32)width, (f32)heigth);
    
    camera->screen_rateo = (f32)width / (f32)heigth;
}

void vx_camera_move_forward(vx_Camera* camera, f32 speed) {
    VX_T(f32, vx_Vec3) temp = camera->front;
    temp.x *= speed;    temp.y *= speed;    temp.z *= speed;

    camera->position.x += temp.x;
    camera->position.y += temp.y;
    camera->position.z += temp.z;
}

void vx_camera_move_backward(vx_Camera* camera, f32 speed) {
    vx_camera_move_forward(camera, -speed);
}

void vx_camera_move_right(vx_Camera* camera, f32 speed) {
    camera->position.x -= sin(vx_deg_to_rad(camera->rotation.x)) * speed;
    camera->position.z += cos(vx_deg_to_rad(camera->rotation.x)) * speed;
}

void vx_camera_move_left(vx_Camera* camera, f32 speed) {
    vx_camera_move_right(camera, -speed);
}

void vx_camera_rotate_x(vx_Camera* camera, f32 amount) {
    camera->rotation.x += amount;
    if (camera->rotation.x >= 360.0f) {
        camera->rotation.x -= 360.0f;
    } else if (camera->rotation.x <= 0.0f) {
        camera->rotation.x += 360.0f;
    }

    update_front(camera);
}

void vx_camera_rotate_y(vx_Camera* camera, f32 amount) {
    camera->rotation.y += amount;
    if (camera->rotation.y > 89.99f) {
        camera->rotation.y = 89.99f;
    } else if (camera->rotation.y < -89.99f) {
        camera->rotation.y = -89.99f;
    }

    update_front(camera);
}

void vx_camera_rotate_z(vx_Camera* camera, f32 amount) {
    camera->rotation.z += amount;
    if (camera->rotation.z >= 360.0f) {
        camera->rotation.z -= 360.0f;
    } else if (camera->rotation.z <= 0.0f) {
        camera->rotation.z += 360.0f;
    }

    update_front(camera);
}

void vx_camera_bind(vx_Camera* camera) {
    update_front(camera);

    VX_T(f32, vx_Vec3) temp = camera->position;
    temp.x += camera->front.x;
    temp.y += camera->front.y;
    temp.z += camera->front.z;

    VX_T(f32, vx_Vec2) world_top;
    world_top.x = cos(vx_deg_to_rad(camera->rotation.z));
    world_top.y = sin(vx_deg_to_rad(camera->rotation.z));

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(camera->fov, camera->screen_rateo, camera->nearz, camera->farz);
    gluLookAt(camera->position.x, camera->position.y, camera->position.z, temp.x, temp.y, temp.z, 0.0, world_top.x, world_top.y);
}

_VX_OPTION_CREATE_BODY_FOR_TYPE(vx_Camera);
_VX_VECTOR_CREATE_BODY_FOR_TYPE(vx_Camera);
