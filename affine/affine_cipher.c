#include <stdio.h>

#include "affine_cipher.h"

const char *DEFAULT_KEY_FILENAME = ".key";


int affine_cipher_write_to_disk(AffineCipher* cipher, char *file_name) {
  FILE *f;
  unsigned long bytes_written;
  char buffer[2];

  if (file_name == NULL) {
    f = fopen(".key", "wb");
  } else {
    f = fopen(file_name, "wb");
  }

  if (!f) {
    fprintf(stderr, "Couldn't open file\n");
    return 1;
  }

  buffer[0] = cipher->a;
  buffer[1] = cipher->b;

  bytes_written = fwrite(buffer, sizeof(char), 2, f);
  if (bytes_written == 0) {
    fprintf(stderr, "Error storing cipher.\n");
    fclose(f);
    return 1;
  } else if (bytes_written < 2) {
    fprintf(stderr, "Write Error\n");
    fclose(f);
    return 1;
  }
  fclose(f);
  return 0;
}

int affine_cihper_read_from_disk(AffineCipher *cipher, char *filename) {
  unsigned long bytes_read;
  FILE *f;
  char buffer[2];

  if (!filename)
    f = fopen(DEFAULT_KEY_FILENAME, "rb");
  else
    f = fopen(filename, "rb");

  if (!f) {
    perror("Problem opening file: ");
    return 1;
  }

  bytes_read = fread(buffer, sizeof(char), 2, f);
  if (!bytes_read) {
    fprintf(stderr, "Couldn't read any bytes!\n");
    fclose(f);
    return 1;
  } else if (bytes_read < 2) {
    fprintf(stderr, "Couldn't read all of the data\n");
    fclose(f);
    return 1;
  } 
  fclose(f);

  cipher->a = buffer[0];
  cipher->b = buffer[1];
  return 0;
}
