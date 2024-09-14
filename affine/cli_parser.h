#ifndef CLI_PARSER_H
#define CLI_PARSER_H

#define COMMAND_COUNT 5

typedef enum {
  COMMAND_DECRYPT,
  COMMAND_ENCRYPT,
  COMMAND_SET_KEY,
  COMMAND_READ_KEY,
  COMMAND_HELP
} Command;

extern const char* command_strings[COMMAND_COUNT];

void parse_command_line(int argc, char **argv);

#endif /* CLI_PARSER_H */
