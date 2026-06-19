#include "include/io.h"

FILE_T* init_file_struct(long length, unsigned char* value, const char* filepath){
    FILE_T* file = calloc(1, sizeof(struct FILE_INFO));
    file->length = length;
    file->data = value;
    file->file_path = filepath;
    file->file_type = detect_file_type(file->data, file->length);
    return file;

}
char* detect_file_type(unsigned char* data, long length){
    char* file_type = "No Type Found";
    if (data[0] == 0xFF &&data[1]== 0xD8 && data[2] == 0xFF){
        file_type = "JPEG";
    }

    return file_type;
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