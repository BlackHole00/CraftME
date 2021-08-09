#pragma once
#include "buffer.h"
#include "layout.h"
#include "../logic/transform.h"
#include <gl/gl.h>

typedef struct {
    GLenum primitive;
    vx_Buffer buffer;

    vx_Position position;
    vx_Rotation rotation;
    vx_Scale scale;
} vx_Mesh;

vx_Mesh vx_mesh_new(GLenum);
vx_Mesh vx_mesh_from_buffer(GLenum, vx_Buffer);
void vx_mesh_free(vx_Mesh*);

void vx_mesh_draw(vx_Mesh*, vx_Layout*);
