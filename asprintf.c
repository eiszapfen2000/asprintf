#include <errno.h>  
#include <stdio.h>
#include <stdlib.h>
#include "asprintf.h"

#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
#ifdef __cplusplus
extern "C"
#endif
int vasprintf(char** strp, const char* fmt, va_list ap)
{
    int formattedLength, actualLength;
    size_t requiredSize;

    // be paranoid
    *strp = NULL;

    // compute length of formatted string, without NULL terminator
    formattedLength = _vscprintf(fmt, ap);

    // bail out on error
    if (formattedLength < 0)
    {
        return -1;
    }

    // allocate buffer, with NULL terminator
    requiredSize = ((size_t)formattedLength) + 1;
    *strp = (char*)malloc(requiredSize);

    // bail out on failed memory allocation
    if (*strp == NULL)
    {
        errno = ENOMEM;
        return -1;
    }

    // write formatted string to buffer, use security hardened _s function
    actualLength = vsnprintf_s(*strp, requiredSize, requiredSize - 1, fmt, ap);

    // again, be paranoid
    if (actualLength != formattedLength)
    {
        free(*strp);
        *strp = NULL;
        errno = EOTHER;
        return -1;
    }

    return formattedLength;
}

#ifdef __cplusplus
extern "C"
#endif
int asprintf(char** strp, const char* fmt, ...)
{
    int result;

    va_list ap;
    va_start(ap, fmt);
    result = vasprintf(strp, fmt, ap);
    va_end(ap);

    return result;
}
#endif
