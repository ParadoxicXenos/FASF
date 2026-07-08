#include "include/write.h"
#include "include/io.h"
#include <stdint.h>
unsigned char magic[6];
unsigned char blob_length[8];

unsigned char* prepare_blob_4_write(unsigned char* data_blob, uint64_t length,unsigned char compression_type){
    magic[0] = 0x46;//F
    magic[1] = 0x41;//A
    magic[2] = 0x53;//S
    magic[3] = 0x46;//F
    magic[4] = 0x02;//VERSION 0.2
    magic[5] = compression_type;//self explanatory
    unsigned char *blob;
    blob = (unsigned char *)malloc((14+length) * sizeof(unsigned char));
    if (blob == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    for (int i = 0; i < 6;i++){
        blob[i] = magic[i];
    }                

    uint64_to_8bytes(length, blob_length);
    for (int i = 0; i < 8;i++){
        blob[i+6] = blob_length[i];
    }
    
    for (int i = 0; i < length;i++){
        blob[i+14] = data_blob[i];
    }
    return blob;
}



int write_to_file(unsigned char* data_blob, uint64_t length, const char* file_path){
    int file_existence = doesFileExist(file_path);
    if (file_existence == 0){
        return 1;
    }

    FILE *fptr;

    fptr = fopen(file_path, "wb");
    fwrite(data_blob, sizeof(unsigned char), length, fptr);//WRITES DATA BLOB
    fclose(fptr); 
    return 0;
}

