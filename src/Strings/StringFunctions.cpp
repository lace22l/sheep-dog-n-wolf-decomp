#include <cstdarg>
#include <cstdio>

//
// Created by Kyle Muñoz Andrades on 6/4/26.
//
char* custom_strcat(char* dst, const char* src)
{
    char* end = dst;

    while (*end) end++;      // find end of dst
    while ((*end++ = *src++)); // copy src including '\0'

    return dst;
}


int custom_sprintf(char* out_buffer, const char* format, ...)
{
    va_list args;
    va_start(args, format);

    int result = vsprintf(out_buffer, format, args);

    va_end(args);

    return result;
}
int custom_strcopy(char* out_buffer, const char* input)
{
    char* start = out_buffer;

    while ((*out_buffer++ = *input++) != '\0') {
        // copy including null terminator
    }

    return (int)(out_buffer - start - 1); // length copied (excluding null)
}