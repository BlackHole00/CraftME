#pragma once

#define GL_CALL(_FUNC) _FUNC; check_gl_error(__FILE__, __LINE__, __FUNCTION__);
#define GL_CHECK_ERRORS() check_gl_error(__FILE__, __LINE__, __FUNCTION__)

void check_gl_error(char*, int, const char*);
