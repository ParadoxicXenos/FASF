#ifndef WRITE_H
#define WRITE_H
#include <stdint.h>
int write_to_file(unsigned char* data_blob, uint64_t length, const char* file_path);
unsigned char* prepare_blob_4_write(unsigned char* data_blob, uint64_t length,unsigned char compression_type);
#endif