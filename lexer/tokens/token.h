#include <stdbool.h>
#ifndef TOKEN_H // header guard
#define TOKEN_H

typedef struct token {
  char *tok;  // {                  | 55
  char *type; // open_parenthesis   | int
  bool split; // true               | false
} token;

#define MAX_TOK_LEN 100
#define MAX_TYPE_LEN 100

// functions
token *splitToken(token *theToken);
bool isSplittableType(char *delim);
void inputToken(token *allTokens, int *allTokenLen, char *tok, char *typ);
void printTokens(token *allTokens, int *allTokensLen);
char *checkType(char *currTok);
token *makeToken(char *tok, char *type, bool split);
token *tokenListAppened(token *tokenList, token *newToken, int *tokenLen);
token *tokenListConcatenate(token *front, int *frontLen, token *back,
                            int *backLen);
int countRepititon(char *string, char *delim);
void freeToken(token *theToken);
#endif // TOKEN_H
