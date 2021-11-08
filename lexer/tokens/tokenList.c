#include "token.h"
#include <float.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// The size of one token, find out how to make this a global var
const int tokenSize2 = (sizeof(token) + (sizeof(char) * MAX_TOK_LEN) +
                        (sizeof(char) * MAX_TYPE_LEN) + sizeof(bool));

/*
  Frees all of the tokens in TOKENLIST, and then frees TOKENLIST.
*/
void freeTokenList(token *tokenList, int tokenLen) {
  for (int i = 0; i < tokenLen && (tokenList + i) != NULL; i++) {
    printf("tokenLen = %d, tokenList + i = %s\n", tokenLen,
           (tokenList + i)->tok);

    freeToken((tokenList + i));
  }
  printf("finished freeing\n");
}

/*
  Returns back the length of the TOKENLIST.
*/
int tokenListLen(token *tokenList) {
  int counter = 0;
  for (int i = 0; (tokenList + i)->tok != NULL; i++, counter++)
    ;
  return counter;
}

/*
  Appends single token NEWTOKEN onto the end of token list TOKENLIST. Returns
  back a pointer to TOKENLISTS' head.
*/
token *tokenListAppened(token *tokenList, token *newToken, int *tokenLen) {

  // If init list
  printf("tokenLen = %d\n", *tokenLen);
  if (*tokenLen == 0) {
    *tokenList = *newToken;
    (*tokenLen)++;
  } else {
    // printSpace();
    (*tokenLen)++;
    tokenList = (token *)realloc(tokenList, (tokenSize2 * (*tokenLen)));
    *(tokenList + (*tokenLen)) = *(newToken);
  }
  // (*tokenLen)++;
  printf("tokenLen = %d ~ newToken->tok = %s\n", *tokenLen, newToken->tok);
  return tokenList;
}

/*
  Concatenates two tokenlists together. Takes token list BACK, and
  concatenatesit onto the end of tokenList FRONT
*/
token *tokenListConcatenate(token *front, int *frontLen, token *back,
                            int *backLen) {
  for (int i = 0; i < (*backLen); i++) {
    front = tokenListAppened(front, (back + i), frontLen);
  }
  // printf("\nprinting tokens after tokenListConcat\n");
  // printTokens(front, frontLen);
  return front;
}
