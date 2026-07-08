#ifndef IO_H
#define IO_H
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
typedef struct FILE_INFO{
    long length;
    unsigned char* data;
    const char* file_path;
    const char* file_type;
    int compression_type;
}FILE_T;

FILE_T* init_file_struct(long length, unsigned char* value, const char* filepath,int compression_type);
FILE_T* load_file(const char* filepath);
int detect_file_compression(unsigned char* data, long length);
int doesFileExist(const char* filename);
void uint64_to_8bytes(uint64_t input, uint8_t out[8]);
uint64_t convert_to_uint64(const uint8_t *array);
#endif
