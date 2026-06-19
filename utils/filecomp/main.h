#ifndef MAIN_H
#define MAIN_H

typedef struct FILE_INFO{
    long length;
    unsigned char* data;
}FILE_T;

int main(int argc, char* argv[]);
FILE_T* load_file(const char* filepath);
FILE_T* init_file_struct(long length, unsigned char* value);
#endif