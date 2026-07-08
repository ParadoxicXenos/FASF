#include "include/main.h"
#include "include/io.h"
#include "include/write.h"
#include "include/compress.h"
#include "include/decompress.h"
#include "include/dnd.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>


extern uint64_t frequency[256];
void print_help(){

    printf("Usage:\n ./fasf.out <\"c\" or \"x\"> <file to compress> <file to save as (MUST FINISH WITH \".fasf\")>\n");
    exit(1);
}

int main(int argc, char* argv[])
{
    int tamper_check = check_dnd();
    if (tamper_check == 1){
        return 1;
    }
    if (argc !=4){
        print_help();
        return 1;
    }

    if (strcmp(argv[1], "c")==0){
        int file_existence = doesFileExist(argv[2]);
        if (file_existence == 1){
            printf("The file you have requested to compress doesnt exist. please double check the path: \"%s\"\n", argv[2]);
            return 1;
        }
        FILE_T* file = load_file(argv[2]);
        count_freq(file->data, file->length);
        FILE_T* compressed_file= RLE_compression(file->data, file->length, argv[3]);
        
        unsigned char* final_blob = prepare_blob_4_write(compressed_file->data, compressed_file->length, 0x01);
        int write_success = write_to_file(final_blob, compressed_file->length+14, argv[3]);
        if (write_success == 1){
            printf("file you have requested to write compressed file to already exists:%s",argv[3]);
            return 1;
        }
        int verif = verif_file(argv[2],final_blob);
        if (verif == 1){
            printf("compression failed, file doesnt extract correctly. (files do not match once extracted)\n");
            return 1;
        }
        if (verif == 0){
            printf("compression succesful. file is available at: %s\n",argv[3]);
            return 1;
        }
        
        return 0;
    }
    if (strcmp(argv[1], "x" )==0){
        int file_existence = doesFileExist(argv[2]);
        if (file_existence == 1){
            printf("The file you have requested to extract doesnt exist. please double check the path: \"%s\"\n", argv[2]);
            return 1;
        }
        FILE_T* file = load_file(argv[2]);
        uint64_t length;
        unsigned char* blob = extract_data(file->data,length);
        write_to_file(blob, length, argv[3]);
        return 0;
    }
}


int verif_file(char* file1,unsigned char* file2)
{
    printf("Beginning file verification");
    FILE_T* data1 = load_file(file1);
    uint64_t extract_length;
    unsigned char * data2 = extract_data(file2, extract_length);
    if (extract_length == data1->length){
        for (int i = 0; i < data1->length; i++){
            if (data1->data[i] != data2[i]){
                return 1;
            }
        }
            return 0;
        }
}

int check_dnd(){
        FILE_T* dnd = load_file("./DONOTDELETE.jpeg");
        for (int i = 0; i < dnd->length; i++){
            if (dnd->data[i] != DONOTDELETE_jpeg[i]){
                return 1;
            }
        }
        return 0;
    
}