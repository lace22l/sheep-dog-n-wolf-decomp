#include "../Strings/StringFunctions.h"
#include "FileInfo.h"

//
// Created by Kyle Muñoz Andrades on 6/4/26.
//
extern int g_fileBytesRead;
extern char* g_pFileName;
extern int g_fileSize;
extern char* g_pEmptyString;
int File_Seek(int handle, int offset, int mode);

int File_Read(FileInfo *fileInfo,void *destBuffer,int bytesToRead)

{
    int bytes;

    bytes = File_ReadBytes(fileInfo->handle, destBuffer, bytesToRead);
    if (bytes == bytesToRead) {
        fileInfo->bytesRemaining = fileInfo->bytesRemaining - bytesToRead;
        g_fileBytesRead = g_fileBytesRead + bytesToRead;
    }
    else {
        bytesToRead = -1;
    }
    return bytesToRead;
}
int File_OpenAndGetSize(const char *filename,FileInfo *fileInfo)

{
    int returnCode;

    custom_strcopy(g_pFileName,g_pEmptyString);
    custom_strcat(g_pFileName,filename);
    returnCode = File_Open(g_pFileName,0x8000);
    fileInfo->handle = returnCode;
    if (fileInfo->handle == -1) {
        returnCode = -1;
    }
    else {
        returnCode = File_Seek(fileInfo->handle,0,2);
        fileInfo->size = returnCode;
        fileInfo->bytesRemaining = fileInfo->size;
        File_Seek(fileInfo->handle,0,0);
        g_fileSize = fileInfo->size;
        g_fileBytesRead = 1;
        returnCode = fileInfo->size;
    }
    return returnCode;
}
