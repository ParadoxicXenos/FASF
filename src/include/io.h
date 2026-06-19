#ifndef IO_H
#define IO_H
#include <stdlib.h>
#include <stdio.h>
typedef struct FILE_INFO{
    long length;
    unsigned char* data;
    const char* file_path;
    const char* file_type;
}FILE_T;

FILE_T* init_file_struct(long length, unsigned char* value, const char* filepath);
FILE_T* load_file(const char* filepath);
char* detect_file_type(unsigned char* data, long length);
#endif
