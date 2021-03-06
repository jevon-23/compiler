#include "token.h"
#include "../../utils/utils.h"
#include "../keyToken/key_token.h"
#include "tokenList.h"
#include <float.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *nilString = "_~NULL~_"; // Meant for null tokens

// The size of one token
const int tokenSize = (sizeof(token) + (sizeof(char) * MAX_TOK_LEN) +
                       (sizeof(char) * MAX_TYPE_LEN) + sizeof(bool));

/*
  Prints the ALLTOKENLEN amount of tokens that are inside of ALLTOKENS
*/
void printTokens(token *allTokens, int *allTokenLen) {
  printf("printing Tokens, expecting %d\n", *allTokenLen);
  printSpace();
  for (int i = 0; i < (*allTokenLen) && (allTokens + i) != NULL; i++) {
    printf("currTok = %s ~ typ = %s\n", (allTokens + i)->tok,
           (allTokens + i)->type);
  }
}

/*
  Free THETOKEN
*/
void freeToken(token *theToken) {
  free(theToken->tok);
  free(theToken->type);
  free(theToken);
}

/*
  Create a token struct based on TOK, TYPE, and SPLIT.
*/
token *makeToken(char *tok, char *type, bool split) {
  token *out = (token *)malloc(tokenSize); // output token

  out->tok = (char *)malloc(sizeof(char) * strlen(tok));
  strcpy(out->tok, tok);

  out->type = (char *)malloc(sizeof(char) * strlen(type));
  strcpy(out->type, type);

  out->split = split;

  return out;
}

/*
  Ran by short circuit, splittable types come before non-splittable types in
  case statement. Takes in a string and attempts to match it to a program
  identifier based on the return value from regex.h (hence the short circuit.)
*/
char *checkType(char *currTok) {
  if (match(currTok, OPEN_BRACKET)) { // {
    return OPEN_BRACKET_TOCKEN;
  } else if (match(currTok, CLOSE_BRACKET)) { // }
    return CLOSE_BRACKET_TOKEN;
  } else if (match(currTok, OPEN_PARENTHESIS)) { // (
    return OPEN_PARENTHESIS_TOKEN;
  } else if (match(currTok, CLOSED_PARENTHESIS)) { // )
    return CLOSED_PARENTHESIS_TOKEN;
  } else if (match(currTok, SEMICOLON)) { // ;
    return SEMICOLON_TOKEN;
  } else if (match(currTok, COMMA)) { // ,
    return COMMA_KEY;
  } else if (match(currTok, INTEGER_KEY)) { // int
    return INTEGER_KEY_TOKEN;
  } else if (match(currTok, RETURN_KEY)) { // return
    return RETURN_KEY_TOKEN;
  } else if (match(currTok, IS_INTEGER)) { // [0-9]+
    return IS_INTEGER_TOKEN;
  } else if (match(currTok, IS_IDENTIFIER_KEY)) { // [\w+]
    return IS_IDENTIFIER_TOKEN;
  }
  return "failed";
}

/*
Checking to see if DELIM is a splittable type.
*/
bool isSplittableType(char *delim) {
  if (!strcmp(delim, OPEN_BRACKET_TOCKEN) ||
      !strcmp(delim, CLOSE_BRACKET_TOKEN) ||
      !strcmp(delim, OPEN_PARENTHESIS_TOKEN) ||
      !strcmp(delim, CLOSED_PARENTHESIS_TOKEN) ||
      !strcmp(delim, SEMICOLON_TOKEN) || !strcmp(delim, COMMA_KEY)) {
    return true;
  }
  return false;
}

/*
  Counts how many times delim sequentially in its next occurence inside of
  string
*/
int countRepititon(char *string, char *delim) {
  int counter = 0;
  char *next = memchr(string, *delim, strlen(string));
  if (next == NULL || !isSplittableType(checkType(delim))) {
    return 0;
  }
  for (int i = 0; i < strlen(next) && (*(next + i) == *next); i++, counter++)
    ;

  return counter;
}

/*
  SplitToken helper function.

  INPUTS:
    Splitter is a delim that we will be using to seperate PREV, the string our
    function is running based off of. We will be using SPLITTER as a delim to

    PREV is the segment of the string that we are currently working with.
    PREVTYPE is the program identifier of PREV.
    THETOKEN is the original token that we are splitting up in the first place
    ALLTOKENS is the list of tokens that has been created from spiltting up
      THETOKEN
    COREKEYS are the keys from key_token.

  OUTPUT:
    pain and hours of work on failed recursion step

*/
token *split(char *splitter, char *prev, char *prevType, token *theToken,
             token *allTokens, int allTokensLen, key_tokens *coreKeys) {

  while (prev != NULL) {
    prevType = checkType(prev);             // Get the type of the next token
    char *key = getKey(prevType, coreKeys); // token for this type

    if (isSplittableType(prevType)) {
      // temporary token to recurse with.
      token *tempTok = makeToken(prev, prevType, true);
      // list of extra tokens that we get from recursive
      token *extras = splitToken(tempTok);
      if (extras != NULL) {
        int extraLen = tokenListLen(extras); // Len(extras)

        // Append extras on to the back of allToks.
        allTokens =
            tokenListConcatenate(allTokens, &allTokensLen, extras, &extraLen);

        // how many times do we see our current delim? input that amount
        int numInp = countRepititon(prev, key);
        int numUsed = 0;
        for (int i = allTokensLen - 2; !strcmp((allTokens + i)->tok, key);
             i--, numUsed++)
          ;

        for (int i = 0; i < abs((numInp - numUsed)); i++) {
          token *input = makeToken(key, prevType, true);
          allTokens = tokenListAppened(allTokens, input, &allTokensLen);
        }
      }
      free(extras);       // free extras
      freeToken(tempTok); // free tempTok
    } else {
      // Add the current token and the delim that we are spliting by.
      token *prefix = makeToken(prev, prevType, false);
      token *delim = makeToken(splitter, theToken->type, true);
      allTokens = tokenListAppened(allTokens, prefix, &allTokensLen);
      allTokens = tokenListAppened(allTokens, delim, &allTokensLen);
    }
    prev = strtok(NULL, splitter); // Go to the next token
  }
  return allTokens;
}

/*
  SPLIT this token into its indiviualized components based on the library.

  This is holdin down my entire lexer right now
*/
token *splitToken(token *theToken) {
  if (!theToken->split) {
    return NULL; // token is not splittable, dont split it
  }
  key_tokens *coreKeys = buildMap(); // built-in c tokens

  // If the token we are given is built-in, return it.
  if (!strcmp(theToken->tok, getKey(theToken->type, coreKeys))) {
    return theToken;
  }

  token *allTokens = (token *)malloc(tokenSize);     // list of all tokens
  int allTokensLen = 1;                              // length of allTokens
  char *splitter = getKey(theToken->type, coreKeys); // tok we are splitting by

  // strtok returns the string that comes before splitter
  char *prev = strtok(theToken->tok, splitter);
  char *prevType = checkType(prev); // type associated w/ prev

  // recurse! returns back all of the tokens after the current token has been
  // split
  return split(splitter, prev, prevType, theToken, allTokens, allTokensLen,
               coreKeys);
}
