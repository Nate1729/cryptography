#include <stdio.h>

#include "cli_parser.h"

int main(int argc, char **argv) {
  char* file_name;

  file_name = parse_command_line(argc, argv);

  if (file_name == NULL) {
    return 1;
  }

  printf("File name is %s\n", file_name);
  return 0;
}
