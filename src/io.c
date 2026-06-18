#include "include/io.h"

FILE_T* init_file_struct(long length, unsigned char* value, const char* filepath){
    FILE_T* file = calloc(1, sizeof(struct FILE_INFO));
    file->length = length;
    file->data = value;
    file->filepath = filepath;
    return file;

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

    return init_file_struct(length,buffer,filepath);
}