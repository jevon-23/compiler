#include "lex.h"
#include "../utils/utils.h"
#include "keyToken/key_token.h"
#include "tokens/token.h"
#include "tokens/tokenList.h"
#include <float.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int sizeOfToken3 = sizeof(token) + (sizeof(char) * MAX_TOK_LEN) +
                         (sizeof(char) * MAX_TYPE_LEN) + sizeof(bool);
/*
  Reads from a file, and tokenizes it
*/

token *lexer(char *fileName) {
  aFile theFile = readFile(fileName);

  printf("read theFile\n");
  token *allTokens = (token *)malloc(sizeOfToken3);
  int allTokensLen = 1;

  allTokens = lexFile(&theFile, allTokens, &allTokensLen);
  return allTokens;
}

token *lexFile(aFile *theFile, token *allTokens, int *allTokenLen) {
  printf("inside of lexFile\n");
  for (int i = 0; i < theFile->lineCount; i++) {
    token *toks = lexLine(*(theFile->contents + i));
    int toksLen = tokenListLen(toks);
    printf("came back from LexLine, got the length, about to concatenate. \n");
    allTokens = tokenListConcatenate(allTokens, allTokenLen, toks, &toksLen);
  }
  return allTokens;
}

/*
  Lex a line. Returns back a list of tokens that this line consists of.
*/
token *lexLine(char *line) {

  // all tokens on this line
  token *allTokens = (token *)malloc(sizeOfToken3);
  int allTokensLen = 1;

  int state = 0;            // state of strtok call
  char *whiteSpace = " \t"; // white space or tab
  // lex a line
  allTokens = lex(line, whiteSpace, allTokens, &allTokensLen, state);
  printf("finished lexLine!\n");
  return allTokens;
}

/*
  When using Strtok, for some reason our pointer turns from the entire string to
  simply the string that occurs before the delim that we are splitting by.
  Because of this functionality, we use state to keep track of how many times
  strtok has been called in order to get its next token back.

  this function returns back a pointer to the state we will be in splititng
  line by delim using strtok() STATE amount of times.
*/
char *getStrTokState(char *line, char *delim, int state) {
  char *currTok = strtok(line, delim);
  for (int i = 0; i < state && currTok != NULL;
       currTok = strtok(NULL, delim), i++)
    ;
  return currTok;
}

/*
  LexLine() helper function.
  Fills up allTokens with tokens found from splitting LINE by DELIM.
*/

token *lex(char *line, char *delim, token *allTokens, int *allTokensLen,
           int state) {
  printf("inside of lex, line = %s\n", line);
  // strtok edits original line, so saving it here for later usage
  char *ogLine = (char *)malloc(sizeof(char) * strlen(line));
  strcpy(ogLine, line);

  // printf("")
  // split our line by whitespaces and tokenize each value.
  char *currTok = getStrTokState(line, delim, state);
  while (currTok != NULL) {
    printf("reading the token = %s\n", currTok);
    // Create a new token
    char *currType = checkType(currTok);
    token *newTok = makeToken(currTok, currType, isSplittableType(currType));

    // Attempt to split the token
    token *postSplit = splitToken(newTok);
    if (postSplit == NULL) {
      // Our original token is not a splittable type -> input into allTokens
      allTokens = tokenListAppened(allTokens, newTok, allTokensLen);
    } else {
      // Our original input token was splittable, may need to input 1+ token
      int postSplitLen = tokenListLen(postSplit);
      printf("postSPlitLen = %d ~ printing tokens\n", postSplitLen);
      printTokens(postSplit, &postSplitLen);
      allTokens = tokenListConcatenate(allTokens, allTokensLen, postSplit,
                                       &postSplitLen);

      // b/c splitToken() is ran all the way through, there will be another
      // strtok() -> our place in strtok stack will be lost. Retreiving state.
      strcpy(line, ogLine);
      currTok = getStrTokState(line, delim, state);
    }
    state++;
    currTok = strtok(NULL, delim);
  }
  return allTokens;
}
