#include "gl_call.h"
#include <gl/gl.h>
#include <stdio.h>

void check_gl_error(char* file_name, int line_num, const char* function_name) {
    GLenum error;
    while((error = glGetError()) != GL_NO_ERROR) {
        char* error_str;
        switch (error) {
            case GL_INVALID_VALUE: {
                error_str = "GL_INVALID_VALUE";
                break;
            }
            case GL_INVALID_ENUM: {
                error_str = "GL_INVALID_ENUM";
                break;
            }
            case GL_INVALID_OPERATION: {
                error_str = "GL_INVALID_OPERATION";
                break;
            }
            case GL_STACK_OVERFLOW: {
                error_str = "GL_STACK_OVERFLOW";
                break;
            }
            case GL_STACK_UNDERFLOW: {
                error_str = "GL_STACK_UNDERFLOW";
                break;
            }
            case GL_OUT_OF_MEMORY: {
                error_str = "GL_OUT_OF_MEMORY";
                break;
            }
            default: {
                error_str = "UNKNOWN GL ERROR! (DRIVER BAD?)";
                break;
            }
        }        

        printf("[GLERROR]: %s(%d) in function %s(%s::%d)\n", error_str, error, function_name, file_name, line_num);
    }
}
