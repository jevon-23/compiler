#include <stdbool.h>
#ifndef TOKEN_H // header guard
#define TOKEN_H

/*
  Expecting inputs from a .c file, token.h is meant to help tokenize .c files
  for lexing.
*/

typedef struct token {
  char *tok;  // {                  | value read from file
  char *type; // open_parenthesis   | program identifier type
  bool split; // true               | if the token is of a splittable type
} token;

// max length of a given token should be no longer than 100 chars.
#define MAX_TOK_LEN 100

// Our types are never going to be longer than 100, might reduce later
#define MAX_TYPE_LEN 100

// functions
token *splitToken(token *theToken); // split theToken into multiple tokens
bool isSplittableType(char *delim); // is this token of a splittabe type?
void inputToken(token *allTokens, int *allTokenLen, char *tok, char *typ);
void printTokens(token *allTokens, int *allTokensLen); // print all tokens
char *checkType(char *currTok); // returns type from based on regex.h
token *makeToken(char *tok, char *type, bool split); // make a token

// counts repitition of delim at the next occurenec inside of string
int countRepititon(char *string, char *delim);

void freeToken(token *theToken); // free
#endif                           // TOKEN_H
