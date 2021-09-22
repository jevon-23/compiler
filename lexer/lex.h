#include "../utils/utils.h"
#include "tokens/token.h"
#include <stdbool.h>
#ifndef LEX_H // header guard
#define LEX_H

#define MAX_TOK_LEN 100
#define MAX_TYPE_LEN 100

// Functions

// // Parses a file and returns back a tokenized verison of it. RV =
// list(tokens) token *mapTokens(aFile *theFile, int *allTokensLen);
//
// // Inputs a token into a map.
// void inputToken(token *allTokens, int *allTokensLen, char *tok, char *typ);

// Parses a line, and return back the individual tokens found in it.
token *lexLine(char *line);

#endif // LEX_H
