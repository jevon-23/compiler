#include "../lex.h"
#include <float.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// FIXME : UPDATE TESTING

void printTokens(token *allTokens, int *allTokenLen) {
  printSpace();
  for (int i = 0; i < *allTokenLen; i++) {
    printf("currTok = %s : typ = %s\n", (allTokens + i)->tok,
           (allTokens + i)->type);
  }
}

void TestMapTokens() {
  aFile theFile = readFile("ret2.c");
  int *allTokensLen = (int *)malloc(sizeof(int));
  token *toks = mapTokens(&theFile, allTokensLen);
  printTokens(toks, allTokensLen);
}

void TestInputToken() {
  token *allTokens =
      (token *)malloc(sizeof(token) + MAX_TOK_LEN + MAX_TYPE_LEN);

  int tokenLen = 1;
  int *allTokenLen = &tokenLen;
  char *currTok = "testTok";
  char *typ = "testType";
  inputToken(allTokens, allTokenLen, currTok, typ);
  printTokens(allTokens, allTokenLen);
}

int main() {
  // printSpace();
  // printf("TESTING TESTINPUT\n");
  // TestInputToken();
  // printSpace();
  // printf("TESTING MAPTOKENS\n");
  // TestMapTokens();
  // printSpace();
}
