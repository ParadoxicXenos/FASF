#include "include/write.h"
#include "include/io.h"
const char* write_to_file(unsigned char* data_blob, const char* file_path, long length){
    
    FILE *fptr;

    fptr = fopen(file_path, "wb");
    
    fwrite(data_blob, sizeof(unsigned char), length, fptr);

    fclose(fptr); 
}
