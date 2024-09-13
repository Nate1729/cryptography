#include <stdio.h>

#include "cli_parser.h"

static void print_info_screen() {
  fprintf(stdout, "Usage: affine  <command>  <command_args>\n\n"
      "Valid commands:\n"
      "  decrypt\n"
      "  encrypt\n"
      "  set-key\n"
      "  read-key\n"
  );
}

void parse_command_line(int argc, char **argv) {
  if (argc == 1) {
    print_info_screen();
    return;
  }
}
