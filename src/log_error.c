#include "log_error.h"

#include "stdio.h"
#include "stdarg.h"
#include "stdlib.h"

void
log_error(bool ex, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    fputs("ERROR: ", stderr);
    vfprintf(stderr, format, args);
    fputc('\n', stderr);
    va_end(args);
    if (ex)
        exit(EXIT_FAILURE);
}