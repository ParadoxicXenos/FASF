#include "include/io.h"

FILE_T* init_file_struct(long length, unsigned char* value, const char* filepath, int compression_type){
    FILE_T* file = calloc(1, sizeof(struct FILE_INFO));
    file->length = length;
    file->data = value;
    file->file_path = filepath;
    if (compression_type == 0){
        file->compression_type = detect_file_compression(file->data, file->length);
    }
    
    return file;

}

int detect_file_compression(unsigned char* data, long length){
    int file_compression = 0;
    if (data[5] == 0x01){
        file_compression = 1;
    }

    return file_compression;
}
FILE_T* load_file(const char* filepath)
{
    unsigned char* buffer = 0;
    long length = 0;

    FILE* f = fopen(filepath, "rb");

    if (f)
    {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);

        buffer = malloc(length);

        if (buffer)
            fread(buffer, 1, length, f);

        fclose(f);
        
    }

    return init_file_struct(length,buffer,filepath,0);
}

// following code is from following source (HAS BEEN MODIFIED BY ME BUT ORIGINAL SOURCE IS HERE): https://stackoverflow.com/q/13945341
int doesFileExist(const char* filename)
{
  FILE* fptr = fopen(filename, "r");
  if (fptr != NULL)
  {
    fclose(fptr);
    return 0;
  }
  return 1;
}

void uint64_to_8bytes(uint64_t input, uint8_t out[8]){
    // NOT MY CODE: Source - https://stackoverflow.com/a/69968094
    out[0] = input >> 0 & 0xFF;
    out[1] = input >> 8 & 0xFF;
    out[2] = input >> 16 & 0xFF;
    out[3] = input >> 24 & 0xFF;
    out[4] = input >> 32 & 0xFF;
    out[5] = input >> 40 & 0xFF;
    out[6] = input >> 48 & 0xFF;
    out[7] = input >> 56 & 0xFF;
}


uint64_t convert_to_uint64(const uint8_t *array) {
    //NOT MY CODE, DONT KNOW SOURCE
    return ((uint64_t)array[7] << 56) |
    ((uint64_t)array[6] << 48) |
    ((uint64_t)array[5] << 40) |
    ((uint64_t)array[4] << 32) |
    ((uint64_t)array[3] << 24) |
    ((uint64_t)array[2] << 16) |
    ((uint64_t)array[1] << 8) |
    ((uint64_t)array[0]);
}