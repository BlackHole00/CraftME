#include "buffer.h"
#include <stdio.h>

vx_Buffer vx_buffer_new() {
    vx_Buffer buffer;

    buffer.data = vx_vector_new();
    buffer.hints = vx_vector_new();
    buffer.hints_layout = vx_vector_new();

    return buffer;
};

void vx_buffer_free(vx_Buffer* buffer) {
    vx_vector_free(&(buffer->data));
    vx_vector_free(&(buffer->hints));
    vx_vector_free(&(buffer->hints_layout));
}

void vx_buffer_clear(vx_Buffer* buffer) {
    vx_vector_clear(&(buffer->data));
    vx_vector_clear(&(buffer->hints));
    vx_vector_clear(&(buffer->hints_layout));
}

void vx_buffer_push_2(vx_Buffer* buffer, f32 value1, f32 value2) {
    vx_buffer_push(buffer, value1);
    vx_buffer_push(buffer, value2);
}

void vx_buffer_push_3(vx_Buffer* buffer, f32 value1, f32 value2, f32 value3) {
    vx_buffer_push(buffer, value1);
    vx_buffer_push(buffer, value2);
    vx_buffer_push(buffer, value3);
}

void vx_buffer_push_4(vx_Buffer* buffer, f32 value1, f32 value2, f32 value3, f32 value4) {
    vx_buffer_push(buffer, value1);
    vx_buffer_push(buffer, value2);
    vx_buffer_push(buffer, value3);
    vx_buffer_push(buffer, value4);
}

void vx_buffer_hint_color3(vx_Buffer* buffer, f32 r, f32 g, f32 b) {
    vx_buffer_hint_raw(buffer, r);
    vx_buffer_hint_raw(buffer, g);
    vx_buffer_hint_raw(buffer, b);

    vx_BufferHintLayoutElement elem = (vx_BufferHintLayoutElement){
        elem: VX_COLOR_3F32,
        start_data: buffer->data.length,
    };
    vx_buffer_hint_layout_raw(buffer, elem);
}

void vx_buffer_hint_color4(vx_Buffer* buffer, f32 r, f32 g, f32 b, f32 a) {
    vx_buffer_hint_raw(buffer, r);
    vx_buffer_hint_raw(buffer, g);
    vx_buffer_hint_raw(buffer, b);
    vx_buffer_hint_raw(buffer, a);

    vx_BufferHintLayoutElement elem = (vx_BufferHintLayoutElement){
        elem: VX_COLOR_4F32,
        start_data: buffer->data.length,
    };
    vx_buffer_hint_layout_raw(buffer, elem);
}

void vx_buffer_draw(vx_Buffer* buffer, vx_Layout* layout, GLenum primitive) {
    glBegin(primitive);

    VX_T(vx_BufferHintLayoutElement, vx_Option) next_hint = VX_T(vx_BufferHintLayoutElement, vx_vector_get)(&(buffer->hints_layout), 0);
    u32 hint_layout_count = 1;
    u32 hint_count = 0;
    u32 layout_count = 0;   /*  The current layout element. */
    u32 data_count = 0;     /*  The current f32 that we are using.  */
    while(data_count < buffer->data.length) {
        if (layout_count >= layout->length) {
            layout_count = 0;
        }
        if (next_hint.is_some) {
            if (data_count >= next_hint.data.start_data) {
                /*  Check the type of hint  */
                switch (next_hint.data.elem) {
                    case VX_COLOR_3F32: {
                        glColor3f(
                            VX_BUFFER_HINTS_DATA(buffer)[hint_count + 0],
                            VX_BUFFER_HINTS_DATA(buffer)[hint_count + 1],
                            VX_BUFFER_HINTS_DATA(buffer)[hint_count + 2]
                        );

                        hint_count += 3;
                        break;
                    }
                    case VX_COLOR_4F32: {
                        glColor4f(
                            VX_BUFFER_HINTS_DATA(buffer)[hint_count + 0], 
                            VX_BUFFER_HINTS_DATA(buffer)[hint_count + 1], 
                            VX_BUFFER_HINTS_DATA(buffer)[hint_count + 2], 
                            VX_BUFFER_HINTS_DATA(buffer)[hint_count + 3]
                        );

                        hint_count += 4;
                        break;
                    }
                    default: {
                        printf("[LAYOUT ERROR]: unknown layout element in hints layout(%d)!", VX_LAYOUT_DATA(layout)[hint_count]);
                    }
                }

                next_hint = VX_T(vx_BufferHintLayoutElement, vx_vector_get)(&(buffer->hints_layout), hint_layout_count);
                hint_layout_count++;
            }
        }

        //  Check the current layout and extract the data from the buffer
        switch(VX_LAYOUT_DATA(layout)[layout_count]) {
            case VX_POSITION_2F32: {
                glVertex2f(
                    VX_BUFFER_DATA(buffer)[data_count + 0], 
                    VX_BUFFER_DATA(buffer)[data_count + 1]
                );
                
                data_count += 2;
                break;
            }
            case VX_POSITION_3F32: {
                glVertex3f(
                    VX_BUFFER_DATA(buffer)[data_count + 0],
                    VX_BUFFER_DATA(buffer)[data_count + 1],
                    VX_BUFFER_DATA(buffer)[data_count + 2]
                );

                data_count += 3;
                break;
            }
            case VX_COLOR_3F32: {
                glColor3f(
                    VX_BUFFER_DATA(buffer)[data_count + 0],
                    VX_BUFFER_DATA(buffer)[data_count + 1],
                    VX_BUFFER_DATA(buffer)[data_count + 2]
                );

                data_count += 3;
                break;
            }
            case VX_COLOR_4F32: {
                glColor4f(
                    VX_BUFFER_DATA(buffer)[data_count + 0], 
                    VX_BUFFER_DATA(buffer)[data_count + 1], 
                    VX_BUFFER_DATA(buffer)[data_count + 2], 
                    VX_BUFFER_DATA(buffer)[data_count + 3]
                );

                data_count += 4;
                break;
            }
            case VX_UV_2F32: {
                glTexCoord2f(
                    VX_BUFFER_DATA(buffer)[data_count + 0], 
                    VX_BUFFER_DATA(buffer)[data_count + 1]
                );

                data_count += 2;
                break;
            }
            default: {
                printf("[LAYOUT ERROR]: unknown layout element(%d)!", VX_LAYOUT_DATA(layout)[layout_count]);
            }
        }

        layout_count++;
    }

    glEnd();
}

_VX_OPTION_CREATE_BODY_FOR_TYPE(vx_BufferHintLayoutElement)
_VX_VECTOR_CREATE_BODY_FOR_TYPE(vx_BufferHintLayoutElement)
