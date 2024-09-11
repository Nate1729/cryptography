#include <stdio.h>

#include "cli_parser.h"

char* parse_command_line(int argc, char **argv) {
  if (argc == 1) {
    fprintf(stderr, "Incorrect usage! You need to provide a filename.\n");
    return NULL;
  }

  if (argc > 2) {
    fprintf(stderr, "Only expected file name, but received more arguments.\n");
    return NULL;
  }
  
  return argv[1];
}
