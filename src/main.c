#include "include/main.h"
#include "include/io.h"
#include "include/write.h"

void print_help(){

    printf("Usage:\n ./fasf.out <filename>\n");
    exit(1);
}

int main(int argc, char* argv[])
{
    FILE_T* file = load_file(argv[1]);
    printf("length: %ld\n", file->length);
    printf("filepath: %s\n", file->file_path);
    printf("data: ");
    for (int i = 0; i<10;i++){
        
        if (i == 9){
            printf(" %X \n", file->data[i]);
        }
        else{
            printf(" %X ", file->data[i]);
        }
    }
    
    printf("file type: %s\n", file->file_type);
    write_to_file(file->data, "bddjdk.fasf", file->length);
    return 0;
}