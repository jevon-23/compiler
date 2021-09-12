#include "lex.h"
#include "../utils/utils.h"
#include "keyToken/key_token.h"
#include "tokens/token.h"
#include <float.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
  Reads from a file, and tokenizes it
*/

// FIXME : UPDATE FILE TP RUN WITH NEW CHANGES TO TOKEN.H AND KEY_TOKEN.H

// void inputToken(token *allTokens, int *allTokensLen, char *tok, char *typ) {
//   allTokens = realloc(allTokens, *allTokensLen + MAX_TOK_LEN + MAX_TYPE_LEN);
//   if (isSplittable(typ)) {
//     printf("splitting token\n");
//     splitToken(allTokens, allTokensLen, tok, typ);
//   }
//   (allTokens + *allTokensLen - 1)->tok =
//       (char *)malloc(sizeof(char) * MAX_TOK_LEN);
//   (allTokens + *allTokensLen - 1)->type =
//       (char *)malloc(sizeof(char) * MAX_TYPE_LEN);
//   strcpy((allTokens + *allTokensLen - 1)->tok, tok);
//   strcpy((allTokens + *allTokensLen - 1)->type, typ);
//   (*allTokensLen)++;
// }

// allTokensLen is a pointer to a malloced space so that it can be filled up.
token *mapTokens(aFile *theFile, int *allTokensLen) {
  // Space for all of the tokens in the file
  token *allTokens =
      (token *)malloc(sizeof(token) + MAX_TOK_LEN + MAX_TYPE_LEN);
  *allTokensLen = 1;
  char *currTok;
  for (int i = 0; i < theFile->lineCount; i++) {
    currTok =
        strtok(*(theFile->contents + i), " "); // Tokenizing by white space
    while (currTok != NULL) {
      char *typ = checkType(currTok);
      inputToken(allTokens, allTokensLen, currTok, typ);
      currTok = strtok(NULL, " ");
    }
  }
  return allTokens;
}
