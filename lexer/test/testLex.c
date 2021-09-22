#include "../lex.h"
#include "../tokens/token.h"
#include "../tokens/tokenList.h"

#include <float.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// FIXME : UPDATE TESTING

// void TestMapTokens() {
//   aFile theFile = readFile("ret2.c");
//   int *allTokensLen = (int *)malloc(sizeof(int));
//   token *toks = mapTokens(&theFile, allTokensLen);
//   printTokens(toks, allTokensLen);
// }
//
// void TestInputToken() {
//   token *allTokens =
//       (token *)malloc(sizeof(token) + MAX_TOK_LEN + MAX_TYPE_LEN);
//
//   int tokenLen = 1;
//   int *allTokenLen = &tokenLen;
//   char *currTok = "testTok";
//   char *typ = "testType";
//   inputToken(allTokens, allTokenLen, currTok, typ);
//   printTokens(allTokens, allTokenLen);
// }

void TestLexLine() {
  char *lineStr = "currLine is test(rand(1, 2, 3))";
  char *line = (char *)malloc(sizeof(char) * strlen(lineStr));
  strcpy(line, lineStr);
  printf("lexing the line: %s\n", line);
  token *out = lexLine(line);
  int allTokensLen = tokenListLen(out);
  printTokens(out, &allTokensLen);
}
int main() {
  // printSpace();
  // printf("TESTING TESTINPUT\n");
  // TestInputToken();
  // printSpace();
  // printf("TESTING MAPTOKENS\n");
  // TestMapTokens();
  // printSpace();
  printSpace();
  TestLexLine();
}
