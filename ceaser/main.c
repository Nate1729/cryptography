#include <errno.h>
#include <stdio.h>

#include "cli_parser.h"
#include "ceaser.h"

int main(int argc, char **argv) {
  char *file_name, c;
  FILE* f;

  file_name = parse_command_line(argc, argv);

  if (file_name == NULL) {
    return 1;
  }

  f = fopen(file_name, "r");
  if (f == NULL) {
    perror("Error opening file: ");
    return errno;
  }

  c = fgetc(f);
  while (c != EOF) {
  }
  fclose(f);

  return 0;
}
