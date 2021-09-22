#include "token.h"
#ifndef TOKEN_H // header guard
#define TOKEN_H

#endif // TOKEN_H

// functions
void freeTokenList(token *tokenList, int tokenLen); // free token list
int tokenListLen(token *tokenList); // returns the length of the list

// appends a NEWTOKEN onto the end of TOKENLIST. Returns a pointer to
// TOKENLISTS' head
token *tokenListAppened(token *tokenList, token *newToken, int *tokenLen);

// concatenates the list of tokens BACK to the list of tokens FRONT. Returns a
// pointer to FRONTS' HEAD
token *tokenListConcatenate(token *front, int *frontLen, token *back,
                            int *backLen);
