#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cli_parser.h"
#include "affine_cipher.h"

const char *command_strings[COMMAND_COUNT] = {
    "decrypt", "encrypt", "set-key", "read-key", "help"
};

const unsigned valid_linear_coefficients[12] ={1,3,5,7,9,11,15,17,19,21,23,25};

static void print_info_screen() {
  unsigned i;
  fprintf(stdout, "Usage: affine  <command>  <command_args>\n\nValid commands:\n");

  for (i=0; i<COMMAND_COUNT; i++) {
    fprintf(stdout, "  %s\n", command_strings[i]);
  }
}

int apply_cipher_to_file(AffineCipher *cipher, char *filename, char (*fn_modifier)(AffineCipher *, char)) {
  FILE *f;
  char c;
  
  f = fopen(filename, "r");
  if (!f) {
    fprintf(stderr, "Issue reading file: %s\n", filename);
    return 1;
  }

  c = fgetc(f);
  while (c != EOF) {
    fprintf(stdout, "%c", fn_modifier(cipher, c));
    c = fgetc(f);
  }

  return 0;
}

void parse_command_line(int argc, char **argv) {
  if (argc == 1) {
    print_info_screen();
    return;
  }

  AffineCipher cipher;
  unsigned long a, b;

  if (!strncmp(command_strings[COMMAND_DECRYPT], argv[1], 10)) {
    /* decryption */
    if (argc > 3) {
      fprintf(stderr, "The encrypt only accepts 1 option, filename.\n");
      return;
    }

    if (affine_cipher_read_from_disk(&cipher, NULL)) {
      fprintf(stderr, "Couldn't retrieve cipher key.\n");
      return;
    }

    apply_cipher_to_file(&cipher, argv[2], affine_cipher_decrypt_char);
  } else if (!strncmp(command_strings[COMMAND_ENCRYPT], argv[1], 10)) {
    /* encryption */
    if (argc > 3) {
      fprintf(stderr, "The encrypt command only accepts 1 option, filename.\n");
      return;
    }
     
    if (affine_cipher_read_from_disk(&cipher, NULL)) {
      fprintf(stderr, "Couldn't retrieve cipher key.\n");
      return;
    }

    apply_cipher_to_file(&cipher, argv[2], affine_cipher_encrypt_char);
  } else if (!strncmp(command_strings[COMMAND_SET_KEY], argv[1], 10)) {
    /* set-key */
    if (argc == 2) {
      fprintf(stderr, "set-key has 2 required parameters, a and b.\n");
      return;
    }

    if (argc == 3) {
      fprintf(stderr, "set-key has 2 required parameters, but only 1 was provided.\n");
      return;
    }
  
    if (argc > 4) {
      fprintf(stderr, "set-key only accepts 2 parameters but %d were given.\n", argc-2);
      return;
    } 

    /* strtoul can't handle if they pass the string "0" so
     * we need to check for that explicitly
     */
    if (argv[2][0] == '0' && argv[2][1] == '\0') {
      fprintf(stderr, "0 is not a valid value for a.\n");
      return;
    }
    if (argv[3][0] == '0' && argv[3][1] == '\0') {
      fprintf(stderr, "0 is not a valid value for b.\n");
      return;
    }
    
    a = strtoul(argv[2], NULL, 10) % 26;
    b = strtoul(argv[3], NULL, 10) % 26;
    if (!a || !b) {
      fprintf(stderr, "One or both cipher key values are invalid.\n");
      return;
    }

    /* a has a restricted domain since decryption requires an
     * inverse element in the ring
     */
    if ((a % 2) && a != 13) {
      cipher.a = a;
      cipher.b = b;
      affine_cipher_write_to_disk(&cipher, NULL);
    } else {
      fprintf(stderr, "a has an invalid format.\n");
      return;
    }
  } else if (!strncmp(command_strings[COMMAND_READ_KEY], argv[1], 10)) {
    /* read-key */
    if (argc > 2) {
      fprintf(stderr, "read-key doesn't support options!\n"); 
      return;
    }

    if (affine_cipher_read_from_disk(&cipher, NULL)) {
      fprintf(stderr, "Couldn't retrieve cipher information.\n");
      return;
    }
    
    fprintf(stdout, "Cipher key is: (%u, %u)\n", cipher.a, cipher.b);
  } else if (!strncmp(command_strings[COMMAND_HELP], argv[1], 10)) {
    print_info_screen(); 
  } else {
    fprintf(stderr, "Invalid command: %s, is not recognized\n\n", argv[1]);
    print_info_screen();
  }
}
