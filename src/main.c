#include "include/main.h"
#include "include/io.h"

void print_help(){

    printf("Usage:\n ./fasf.out <filename>\n");
    exit(1);
}

int main(int argc, char* argv[])
{
    FILE_T* file = load_file(argv[1]);
    printf("length: %ld\n", file->length);
    printf("filepath: %s\n", file->filepath);
    printf("data: %X %X %X %X %X\n", file->data[0], file->data[1], file->data[2], file->data[3], file->data[4]);
    
    return 0;
}