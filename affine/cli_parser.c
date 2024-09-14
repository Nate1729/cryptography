#include <stdio.h>
#include <string.h>

#include "cli_parser.h"

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
    /* TODO read-key */
    fprintf(stdout, "You selected read-key\n");
  } else if (!strncmp(command_strings[COMMAND_HELP], argv[1], 10)) {
    print_info_screen(); 
  } else {
    fprintf(stderr, "Invalid command: %s, is not recognized\n\n", argv[1]);
    print_info_screen();
  }
}
