#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int affine_cipher_read_from_disk(AffineCipher *cipher, char *filename) {
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

char affine_cipher_encrypt_char(AffineCipher *cipher, char c) {
  /* This needs to be _at least_ 2 bytes otherwise
   * we will overflow since we could have to do 25*26=625
   */
  unsigned int offset, index, encrypted_index;

  if (c >= 'a' && c <= 'z') {
    /* lowercase */
    offset = 'a';
  } else if (c >= 'A' && c <= 'Z') {
    /* uppercase */
    offset = 'A';
  } else {
    /* not a character we encrypt */
    return c;
  }

  index = c - offset;
  encrypted_index = (index*cipher->a + cipher->b) % 26;

  return encrypted_index + offset;
}

char affine_cipher_decrypt_char(AffineCipher *cipher, char c) {
  unsigned inverse_ring_elements[26] = { 0 };
  inverse_ring_elements[1] = 1; 
  inverse_ring_elements[3] = 9; 
  inverse_ring_elements[5] = 21; 
  inverse_ring_elements[7] = 15; 
  inverse_ring_elements[9] = 3; 
  inverse_ring_elements[11] = 19; 
  inverse_ring_elements[15] = 7; 
  inverse_ring_elements[17] = 23; 
  inverse_ring_elements[19] = 11; 
  inverse_ring_elements[21] = 5; 
  inverse_ring_elements[23] = 17; 
  inverse_ring_elements[25] = 25; 

  unsigned encrypted_index, index, offset;

  if (c >= 'a' && c <= 'z') {
    offset = 'a';
  } else if (c >= 'A' && c <= 'Z') {
    offset = 'A';
  } else {
    /* Non encrypt/decrypt-able character
     */
    return c;
  }

  if (inverse_ring_elements[cipher->a % 26] == 0) {
    fprintf(stderr, "Found invalid cipher\n");
    exit(1);
  }
  
  encrypted_index = c - offset; 
  index = inverse_ring_elements[(cipher->a) % 26] * (encrypted_index + 26 - ((cipher->b) %26));

  return (index % 26) + offset;
}
