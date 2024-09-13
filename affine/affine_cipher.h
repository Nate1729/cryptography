#ifndef AFFINE_CIPHER_H
#define AFFINE_CIPHER_H


extern const char *DEFAULT_KEY_FILENAME;

typedef struct {
  char a;
  char b;
} AffineCipher;

int affine_cipher_write_to_disk(AffineCipher *c, char *filename);
int affine_cihper_read_from_disk(AffineCipher *c, char *filename);

#endif /* AFFINE_CIPHER_H */
