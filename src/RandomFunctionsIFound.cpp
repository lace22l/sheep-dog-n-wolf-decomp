//
// Created by laceperro on 4/2/2026.
//
#include <cstdarg>
#include <cstdio>
#include <windows.h>
extern char g_path_Demos[];
extern char g_path_Ending[];
extern char g_path_Fend[];
extern char g_path_Scene[];
extern char g_path_Intro[];
extern char g_path_Wheel[];
extern char g_path_Levels[];

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
void GetExeDirectory(char *out_exeDir)

{
    LPSTR cmdLine;
    char *pCursor;

    cmdLine = GetCommandLineA();
    custom_strcopy(out_exeDir,cmdLine);
    pCursor = out_exeDir;
    if ((out_exeDir != (char *)0x0) && (*out_exeDir != '\0')) {
        if (*out_exeDir == '\"') {
            for (; pCursor[1] != '\0'; pCursor = pCursor + 1) {
                *pCursor = pCursor[1];
            }
        }
        else {
            for (; *pCursor != '\0'; pCursor = pCursor + 1) {
            }
        }
        for (; ((out_exeDir < pCursor && (*pCursor != '\\')) && (*pCursor != '/'));
            pCursor = pCursor + -1) {
            }
        if ((*pCursor == '\\') || (*pCursor == '/')) {
            *pCursor = '\0';
        }
    }
    ;
}
void GetLevelPath(char *out_path,char levelId)

{
    switch(levelId) {
        case -7:
            custom_sprintf(out_path,g_path_Demos,4);
            break;
        case -6:
            custom_sprintf(out_path,g_path_Demos,3);
            break;
        case -5:
            custom_strcopy(out_path,g_path_Ending);
            break;
        case -4:
            custom_strcopy(out_path,g_path_Fend);
            break;
        case -3:
            custom_strcopy(out_path,g_path_Scene);
            break;
        case -2:
            custom_strcopy(out_path,g_path_Intro);
            break;
        case -1:
            custom_strcopy(out_path,g_path_Wheel);
            break;
        default:
            custom_sprintf(out_path,g_path_Levels,(int)levelId,(int)levelId);
    }
}