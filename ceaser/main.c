#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "cli_parser.h"
#include "ceaser.h"

int main(int argc, char **argv) {
  char c;
  FILE* f;
  CliState *state;

  state = parse_command_line(argc, argv);
  if (state == NULL) {
    return 1;
  }

  if (state->file_name == NULL) {
    return 1;
  }

  f = fopen(state->file_name, "r");
  if (f == NULL) {
    perror("Error opening file: ");
    return errno;
  }

  for (c=fgetc(f); c != EOF; c=fgetc(f)){
    fprintf(stdout, "%c", encrypt(state->key, c));
  }
  fclose(f);
  free(state);

  return 0;
}
