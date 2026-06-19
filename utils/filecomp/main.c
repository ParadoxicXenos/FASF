#include "main.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{
    FILE_T* data1 = load_file(argv[1]);
    FILE_T* data2 = load_file(argv[2]);
    if (data1->length == data2->length){
        for (int i = 0; i < data1->length; i++){
            if (data1->data[i] != data2->data[i]){
                return 1;
            }
        }
        printf("Well its identical\n");
        return 0;
    }
    else{
        return 1;
    }

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

    return init_file_struct(length,buffer);
}

FILE_T* init_file_struct(long length, unsigned char* value){

    FILE_T* file = calloc(1, sizeof(struct FILE_INFO));

    file->length = length;
    file->data = value;
    
    
    return file;
}
