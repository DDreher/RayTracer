#include "Log.h"

#include <stdio.h>
#include <stdarg.h>

void Log::PrintLine(const char* format_text, ...)
{
    va_list args;
    va_start(args, format_text);
    vprintf(format_text, args);
    va_end(args);
    printf("\n");
}
