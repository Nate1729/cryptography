#ifndef CLI_PARSER
#define CLI_PARSER

typedef enum {
  CRYPTO_OPERATION_ENCRYPT,
  CRYPTO_OPERATION_DECRYPT
} CryptoOperation;

typedef struct {
  char* file_name;
  unsigned key;
  CryptoOperation op;
} CliState;


/* parse the command line information and return the
 * filename to apply the cipher
 */
CliState* parse_command_line(int argc, char **argv);

#endif /* CLI_PARSER */
