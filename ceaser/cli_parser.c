#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cli_parser.h"

CliState* parse_command_line(int argc, char **argv) {
  char *file_name, *raw_operation, *raw_key;
  unsigned long key;
  CryptoOperation op;
  CliState *state;

  if (argc < 4) {
    fprintf(stderr, "Incorrect usage!\n");
    return NULL;
  }

  if (argc > 4) {
    fprintf(stderr, "Received too many inputs.\n");
    return NULL;
  }

  raw_operation = argv[1];
  file_name     = argv[2];
  raw_key       = argv[3];

  /* TODO Should check the length of raw_operation
   * otherwise this isn't a direct string comparision,
   * it's a sub-string comparison
   */
  if (!strncmp(raw_operation, "encrypt", 7)) {
    op = CRYPTO_OPERATION_ENCRYPT;
  } else if (!strncmp(raw_operation, "decrypt", 7)) {
    op = CRYPTO_OPERATION_DECRYPT;
  } else {
    fprintf(stderr, "Invalid operation!\n");
    return NULL;
  }

  key = strtoul(raw_key, NULL, 10);
  if (key == 0) {
    fprintf(stderr, "Invalid key format\n");
    return NULL;
  }

  if (key > 25) {
    fprintf(stderr, "Key size is too big!\n");
    return NULL;
  }

  state = malloc(sizeof(CliState));
  if (state == NULL) {
    fprintf(stderr, "Internal error: Cannot create state.\n");
    return NULL;
  }

  state->key = (unsigned)key;
  state->file_name = file_name;
  state->op = op;

  return state;
}
