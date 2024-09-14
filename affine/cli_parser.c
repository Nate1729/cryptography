#include <stdio.h>
#include <string.h>

#include "cli_parser.h"
#include "affine_cipher.h"

const char *command_strings[COMMAND_COUNT] = {
    "decrypt", "encrypt", "set-key", "read-key", "help"
};

static void print_info_screen() {
  unsigned i;
  fprintf(stdout, "Usage: affine  <command>  <command_args>\n\nValid commands:\n");

  for (i=0; i<COMMAND_COUNT; i++) {
    fprintf(stdout, "  %s\n", command_strings[i]);
  }
}

void parse_command_line(int argc, char **argv) {
  if (argc == 1) {
    print_info_screen();
    return;
  }

  AffineCipher cipher;

  if (!strncmp(command_strings[COMMAND_DECRYPT], argv[1], 10)) {
    /* TODO decryption */
    fprintf(stdout, "You selected decryption\n");
  } else if (!strncmp(command_strings[COMMAND_ENCRYPT], argv[1], 10)) {
    /* TODO encryption */
    fprintf(stdout, "You selected encryption\n");
  } else if (!strncmp(command_strings[COMMAND_SET_KEY], argv[1], 10)) {
    /* TODO set-key */
    fprintf(stdout, "You selected set-key\n");
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
    
    fprintf(stdout, "Cipher key is: (%c, %c)\n", cipher.a, cipher.b);
  } else if (!strncmp(command_strings[COMMAND_HELP], argv[1], 10)) {
    print_info_screen(); 
  } else {
    fprintf(stderr, "Invalid command: %s, is not recognized\n\n", argv[1]);
    print_info_screen();
  }
}
