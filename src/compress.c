#include "include/compress.h"
#include <stdint.h>
uint64_t frequency[256] = {0};

void count_freq(unsigned char* data_blob, long length){
    unsigned char buffer= '\0'; 
    for (int i =0; i < length; i++){
        buffer = data_blob[i];
        frequency[buffer]++;
    }
}

FILE_T* RLE_compression(unsigned char* data_blob, long length, const char* result_filepath){
    unsigned char curr_value = '\0';
    unsigned char prev_value = '\0';
    unsigned char consecutive_instances = 0;
    uint64_t byte_pos_blob = 0;

    unsigned char *blob;
    blob = (unsigned char *)malloc(2 * sizeof(unsigned char));
    if (blob == NULL) {
       printf("Memory allocation failed\n");
       return NULL;
    }

    for (int i = 0; i < length;i++){
        prev_value = curr_value;
        curr_value = data_blob[i];
        if(i == 0){
            consecutive_instances = 1;
        }//check, if its the first byte, if so add 1 to consecutive instances
        if (i > 0){
            if (prev_value == curr_value){
                consecutive_instances++;
            }
            if (prev_value != curr_value || consecutive_instances == 255){
                blob[byte_pos_blob] = consecutive_instances;
                byte_pos_blob++;
                blob[byte_pos_blob] = prev_value;
                byte_pos_blob++;
                consecutive_instances = 1;
                
                unsigned char *temp = realloc(blob, (byte_pos_blob + 2) * sizeof(unsigned char));
                if (temp == NULL) {
                printf("Memory reallocation failed\n");
                free(blob);
                return NULL;
                
                }
                blob = temp;
    
            }
        }

    }
    blob[byte_pos_blob] = consecutive_instances;
    byte_pos_blob++;
    blob[byte_pos_blob] = prev_value;
    byte_pos_blob++;
                
    unsigned char *temp = realloc(blob, (byte_pos_blob + 2) * sizeof(unsigned char));
    if (temp == NULL) {
    printf("Memory reallocation failed\n");
    free(blob);
    return NULL;
                
    }
    blob = temp;
    return init_file_struct(byte_pos_blob, blob, result_filepath, 1);
}
