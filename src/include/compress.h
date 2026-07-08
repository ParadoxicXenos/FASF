#ifndef COMPRESS_H
#define COMPRESS_H
#include <stdint.h>
#include "io.h"
void count_freq(unsigned char* data_blob, long length);
FILE_T* RLE_compression(unsigned char* data_blob, long length, const char* result_filepath);
#endif