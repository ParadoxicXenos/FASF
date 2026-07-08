#include "include/decompress.h"
#include "include/io.h"
#include <stdint.h>
unsigned char * extract_data(unsigned char *data,uint64_t length_out) {
  uint8_t blob_length[8];
  unsigned char *blob;
  uint64_t write_pos = 0;

  if (data[0] != 0x46 || data[1] != 0x41 || data[2] != 0x53 ||
      data[3] != 0x46) {
    printf("NOT AN FASF FILE");
    exit(1);
  }
  if (data[5] == 0x01) { // RLE
    for (int i = 0; i < 8; i++) {
      blob_length[i] = data[i + 6];
    }
    uint64_t length = convert_to_uint64(blob_length);
    unsigned char just_data_compressed[length];
    for (int i = 0; i < length; i++) {
      just_data_compressed[i] = data[i + 14];
    }
    // parse like so: odd numbers = data byte && even/0 = frequency byte
    // repeat the data byte for every number in the frequnecy byte
    unsigned char buffer = '\0';
    int length_decompressed = 0;
    uint8_t freq = '\0';

    for (int i = 0; i < length; i++) {
      if (i % 2 == 0 || i == 0) {
        length_decompressed = length_decompressed + just_data_compressed[i];
      }
    }
    blob =
        (unsigned char *)malloc((length_decompressed) * sizeof(unsigned char));
    if (blob == NULL) {
      printf("Memory allocation failed\n");
      return NULL;
    }
    for (int i = 0; i < length; i++) {
      buffer = just_data_compressed[i];
      if (i % 2 == 0 || i == 0) {
        freq = buffer;
      }
      if (i % 2 != 0 && i != 0) {
        for (int i = 0; i < freq; i++) {
          blob[write_pos] = buffer;
          write_pos++;
        }
      }
    }
  }
  return blob;
}