#include "token.h"
#ifndef TOKEN_H // header guard
#define TOKEN_H

#endif // TOKEN_H

// functions
void freeTokenList(token *tokenList, int tokenLen);
int tokenListLen(token *tokenList);
token *tokenListAppened(token *tokenList, token *newToken, int *tokenLen);
token *tokenListConcatenate(token *front, int *frontLen, token *back,
                            int *backLen);
