#include "lex.h"
#include <float.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  Reads from a file, and tokenizes it
*/

// Tokens
#define OPEN_BRACKET "{"
#define OPEN_BRACKET_TOCKEN "open_bracket" // {
#define CLOSE_BRACKET "}"
#define CLOSE_BRACKET_TOKEN "close_bracket" // }
#define OPEN_PARENTHESIS "("
#define OPEN_PARENTHESIS_TOKEN "open_parenthesis"
#define CLOSED_PARENTHESIS ")"
#define CLOSED_PARENTHESIS_TOKEN "closed_parenthesis"
#define SEMICOLON ";\0"
#define SEMICOLON_TOKEN "semi_colon" // ;
#define INTEGER_KEY "int"
#define INTEGER_KEY_TOKEN "int_key" // int
#define RETURN_KEY "return"
#define RETURN_KEY_TOKEN "ret_key" // return
#define IS_INTEGER "[:0-9:]"
#define IS_INTEGER_TOKEN "is_int" // [0-9]+

// https://pubs.opengroup.org/onlinepubs/7908799/xsh/regcomp.html
bool match(const char *string, char *pattern) {
  int status;
  regex_t re;

  if (regcomp(&re, pattern, 0) != 0) {
    return false; /* report error */
  }
  status = regexec(&re, string, (size_t)0, NULL, 0);
  regfree(&re);
  if (status != 0) {
    return false; /* report error */
  }
  return true;
}

char *checkType(char *currTok) {
  // printf("currTok = %s atoi = %d\n", currTok, (int)currTok[0]);
  if (match(currTok, OPEN_BRACKET)) {
    return OPEN_BRACKET_TOCKEN;
  } else if (match(currTok, CLOSE_BRACKET)) {
    return CLOSE_BRACKET_TOKEN;
  } else if (match(currTok, SEMICOLON)) {
    return SEMICOLON_TOKEN;
  } else if (match(currTok, INTEGER_KEY)) {
    return INTEGER_KEY_TOKEN;
  } else if (match(currTok, RETURN_KEY)) {
    return RETURN_KEY_TOKEN;
  } else if (match(currTok, IS_INTEGER)) {
    return IS_INTEGER_TOKEN;
  } else if (match(currTok, OPEN_PARENTHESIS)) {
    return OPEN_PARENTHESIS_TOKEN;
  } else if (match(currTok, CLOSED_PARENTHESIS)) {
    return CLOSED_PARENTHESIS_TOKEN;
  }
  return "failed";
}

void inputToken(token *allTokens, int *allTokensLen, char *tok, char *typ) {
  allTokens = realloc(allTokens, *allTokensLen + MAX_TOK_LEN + MAX_TYPE_LEN);
  (allTokens + *allTokensLen - 1)->tok =
      (char *)malloc(sizeof(char) * MAX_TOK_LEN);
  (allTokens + *allTokensLen - 1)->type =
      (char *)malloc(sizeof(char) * MAX_TYPE_LEN);
  strcpy((allTokens + *allTokensLen - 1)->tok, tok);
  strcpy((allTokens + *allTokensLen - 1)->type, typ);

  // (allTokens + *allTokensLen - 1)->tok = tok;
  // (allTokens + *allTokensLen - 1)->type = typ;
  (*allTokensLen)++;
}

token *mapTokens(aFile *theFile) {
  // Space for all of the tokens in the file
  token *allTokens =
      (token *)malloc(sizeof(token) + MAX_TOK_LEN + MAX_TYPE_LEN);
  int allTokensLen = 1;
  char *currTok;
  for (int i = 0; i < theFile->lineCount; i++) {
    currTok =
        strtok(*(theFile->contents + i), " "); // Tokenizing by white space
    printf("str = %s top currTok[%d] = %s\n", *(theFile->contents + i), i,
           currTok);
    while (currTok != NULL) {
      char *typ = checkType(currTok);

      inputToken(allTokens, &allTokensLen, currTok, typ);

      currTok = strtok(NULL, " ");
    }
  }

  for (int i = 0; i < allTokensLen - 1; i++) {
    printf("token[%d]. tok = %s type = %s\n", i, (allTokens + i)->tok,
           (allTokens + i)->type);
  }
  return allTokens;
}
