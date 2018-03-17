#ifndef ASPRINTF_H_
#define ASPRINTF_H_

#include <stdarg.h>

#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
#ifdef __cplusplus
extern "C"
{
#endif

int vasprintf(char** ptr, const char* format, va_list ap);
int asprintf(char** ptr, const char* format, ...);

#ifdef __cplusplus
}
#endif
#endif

#endif
