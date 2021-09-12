#include "../../../utils/utils.h"
#include "../token.h"
#include <float.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int sizeOfToken = sizeof(token) + (sizeof(char) * MAX_TOK_LEN) +
                        (sizeof(char) * MAX_TYPE_LEN) + sizeof(bool);

void TestCountRepitition() {
  printSpace();
  char *string = "val((fssf";
  char *delim = "(";
  int out = countRepititon(string, delim);
  printf("string = %s, delim = %s, output = %d\n", string, delim, out);
}

void TestTokenListConcatenate() {
  token *front = (token *)malloc(sizeOfToken * 2);
  token *back = (token *)malloc(sizeOfToken * 2);
  int flen = 3;
  int blen = 3;
  char *testf1 = "testf1";
  char *testf2 = "testf2";
  char *testb1 = "testb1";
  char *testb2 = "testb2";
  char *tok = "token1";
  char *tok2 = "token2";

  front = makeToken(testf1, tok, false);
  *(front + 1) = *(token *)makeToken(testf2, tok, true);

  back = makeToken(testb1, tok2, false);
  *(back + 1) = *(token *)makeToken(testb2, tok2, true);

  front = tokenListConcatenate(front, &flen, back, &blen);
  printTokens(front, &flen);
}

void TestTokenListAppend() {
  token *tokenList = (token *)malloc(sizeOfToken);
  int *tokenLen = malloc(sizeof(int));
  *tokenLen = 1;
  char *test = "test";
  char *tok = "token";

  token *newToken = makeToken(test, tok, true);
  tokenListAppened(tokenList, newToken, tokenLen);

  char *test2 = "test2";
  char *tok2 = "tok2";

  token *newToken2 = makeToken(test2, tok2, false);
  tokenList = tokenListAppened(tokenList, newToken2, tokenLen);

  printf("Printing all tokens. tokenLen = %d\n", *tokenLen);
  for (int i = 0; i < *tokenLen || !strcmp((tokenList + i)->tok, "_~Null~_");
       i++) {
    printf("(tokenList + %d)->tok = %s\n", i, (tokenList + i)->tok);
    printf("(tokenList + %d)->type = %s\n", i, (tokenList + i)->type);
    printf("(tokenList + %d)->split = %d\n", i, (tokenList + i)->split);
  }
}

void TestMakeToken() {
  char *tok = "token";
  char *type = "type";
  bool split = false;

  token *test = makeToken(tok, type, split);
  printf("test->tok = %s\n", test->tok);
  printf("test->type = %s\n", test->type);
  printf("test->bool = %d\n", test->split);
}

void TestSplitToken() {
  token testToken;
  char *tok = "test(rand(1, bye));";
  char *typ = checkType(tok);

  printf("typ = %s\n", typ);
  testToken.tok = (char *)malloc(sizeof(char) * strlen(tok));
  testToken.type = (char *)malloc(sizeof(char) * strlen(typ));
  strcpy(testToken.tok, tok);
  strcpy(testToken.type, typ);
  testToken.split = true;
  token *allTokens = splitToken(&testToken);
  int x = 100;
  printf("tok = %s\n", tok);
  printTokens(allTokens, &x);
}

void TestCheckType() {
  char *t1 = checkType("int");
  char *t2 = checkType("main");
  char *t3 = checkType("{");
  char *t4 = checkType("(");
  char *t5 = checkType("2");
  char *t6 = checkType("}");
  char *t7 = checkType("Main()");
  char *t8 = checkType("main2");

  printf("t1 = int = %s, t2 = main =  %s, t3 = { = %s t4 = ( = %s, t5 = 2 = %s",
         t1, t2, t3, t4, t5);
  printf(" t6 = } = %s, t7 = Main() = %s, t8 = main2 = %s", t6, t7, t8);
}

int main() {
  // TestInputToken();
  TestSplitToken();
  // TestMakeToken();
  // TestTokenListAppend();
  // TestTokenListConcatenate();
  // TestCountRepitition();
}
