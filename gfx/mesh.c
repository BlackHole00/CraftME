#include "mesh.h"

vx_Mesh vx_mesh_new(GLenum primitive) {
    vx_Mesh mesh;
    mesh.buffer     = vx_buffer_new();
    mesh.primitive  = primitive;
    mesh.position   = VX_POSITION_NEW(0.0f, 0.0f, 0.0f);
    mesh.rotation   = VX_ROTATION_NEW(0.0f, 0.0f, 0.0f);
    mesh.scale      = VX_SCALE_NEW(1.0f, 1.0f, 1.0f);
    return mesh;
}

vx_Mesh vx_mesh_from_buffer(GLenum primitive, vx_Buffer buffer) {
    vx_Mesh mesh;
    mesh.buffer     = buffer;
    mesh.primitive  = primitive;
    mesh.position   = VX_POSITION_NEW(0.0f, 0.0f, 0.0f);
    mesh.rotation   = VX_ROTATION_NEW(0.0f, 0.0f, 0.0f);
    mesh.scale      = VX_SCALE_NEW(1.0f, 1.0f, 1.0f);
    return mesh;
}

void vx_mesh_draw(vx_Mesh* mesh, vx_Layout* layout) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    //glLoadIdentity();
    glTranslatef(mesh->position.x, mesh->position.y, mesh->position.z);
    glRotatef(mesh->rotation.x, 1.0f, 0.0f, 0.0f);
    glRotatef(mesh->rotation.y, 0.0f, 1.0f, 0.0f);
    glRotatef(mesh->rotation.z, 0.0f, 0.0f, 1.0f);
    glScalef(mesh->scale.x, mesh->scale.y, mesh->scale.z);

    vx_buffer_draw(&(mesh->buffer), layout, mesh->primitive);

    glPopMatrix();
}

void vx_mesh_free(vx_Mesh* mesh) {
    vx_buffer_free(&mesh->buffer);
}

