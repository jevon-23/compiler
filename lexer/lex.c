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

// FIXME : UPDATE FILE TP RUN WITH NEW CHANGES TO TOKEN.H AND KEY_TOKEN.H

// void inputToken(token *allTokens, int *allTokensLen, char *tok, char *typ) {
//   allTokens = realloc(allTokens, *allTokensLen + MAX_TOK_LEN + MAX_TYPE_LEN);
//   if (isSplittable(typ)) {
//     printf("splitting token\n");
//     splitToken(allTokens, allTokensLen, tok, typ);
//   }
//   (allTokens + *allTokensLen - 1)->tok =
//       (char *)malloc(sizeof(char) * MAX_TOK_LEN);
//   (allTokens + *allTokensLen - 1)->type =
//       (char *)malloc(sizeof(char) * MAX_TYPE_LEN);
//   strcpy((allTokens + *allTokensLen - 1)->tok, tok);
//   strcpy((allTokens + *allTokensLen - 1)->type, typ);
//   (*allTokensLen)++;
// }

// allTokensLen is a pointer to a malloced space so that it can be filled up.
// token *mapTokens(aFile *theFile, int *allTokensLen) {
//   // Space for all of the tokens in the file
//   token *allTokens =
//       (token *)malloc(sizeof(token) + MAX_TOK_LEN + MAX_TYPE_LEN);
//   *allTokensLen = 1;
//   char *currTok;
//   for (int i = 0; i < theFile->lineCount; i++) {
//     currTok =
//         strtok(*(theFile->contents + i), " "); // Tokenizing by white space
//     while (currTok != NULL) {
//       char *typ = checkType(currTok);
//       inputToken(allTokens, allTokensLen, currTok, typ);
//       currTok = strtok(NULL, " ");
//     }
//   }
//   return allTokens;
// }

// token *lexFile(char *fileName) {
//   aFile theFile = readFile(fileName);
//   int *allTokensLen = (int *)malloc(sizeof(int));
//   token *lexTokens = mapTokens(&theFile, allTokensLen);
//   return lexTokens;
// }

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

  // strtok edits original line, so saving it here for later usage
  char *ogLine = (char *)malloc(sizeof(char) * strlen(line));
  strcpy(ogLine, line);

  // split our line by whitespaces and tokenize each value.
  char *currTok = getStrTokState(line, delim, state);
  while (currTok != NULL) {
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
  return allTokens;
}
