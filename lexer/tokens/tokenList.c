#include "token.h"
#include <float.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// The size of one token, find out how to make this a global var
const int tokenSize2 = (sizeof(token) + (sizeof(char) * MAX_TOK_LEN) +
                        (sizeof(char) * MAX_TYPE_LEN) + sizeof(bool));

void freeTokenList(token *tokenList, int tokenLen) {
  for (int i = 0; i < tokenLen; i++) {
    freeToken((tokenList + i));
  }
}

// Counts the length of a tokenList.
int tokenListLen(token *tokenList) {
  int counter = 0;
  for (int i = 0; (tokenList + i)->tok != NULL; i++) {
    counter++;
  }
  return counter;
}

// Appends a token to a list.
token *tokenListAppened(token *tokenList, token *newToken, int *tokenLen) {

  // If init list
  if (*tokenLen == 1) {
    *tokenList = *newToken;
    (*tokenLen)++;
  } else {
    tokenList = (token *)realloc(tokenList, (tokenSize2 * ++(*tokenLen)));
    *(tokenList + (*tokenLen - 2)) = *(newToken);
  }
  return tokenList;
}

// Appends two token Lists together
token *tokenListConcatenate(token *front, int *frontLen, token *back,
                            int *backLen) {
  for (int i = 0; i < (*backLen) - 1; i++) {
    front = tokenListAppened(front, (back + i), frontLen);
  }
  return front;
}
