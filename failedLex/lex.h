#include "utils/utils.h"
#ifndef LEX_H  // header guard
#define LEX_H

typedef struct token {
  char *tok;
  char *type;
} token;

#define MAX_TOK_LEN 100
#define MAX_TYPE_LEN 100

token* mapTokens(aFile *theFile);
#endif // PARSER_H
