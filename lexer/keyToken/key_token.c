#include "key_token.h"
#include <float.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define numMapKeys 10 // the amount of keys that we regex for

// Returns a list of all of the tokens in the key_token map
char **getMapTokens() {
  char **out = (char **)malloc(numMapKeys);
  for (int i = 0; i < numMapKeys; i++) {
    *(out + i) = (char *)malloc(sizeof(char) * 15);
  }
  *(out) = OPEN_BRACKET_TOCKEN;
  *(out + 1) = CLOSE_BRACKET_TOKEN;
  *(out + 2) = OPEN_PARENTHESIS_TOKEN;
  *(out + 3) = CLOSED_PARENTHESIS_TOKEN;
  *(out + 4) = COMMA_KEY;
  *(out + 5) = SEMICOLON_TOKEN;
  *(out + 6) = INTEGER_KEY_TOKEN;
  *(out + 7) = RETURN_KEY_TOKEN;
  *(out + 8) = IS_INTEGER_TOKEN;
  *(out + 9) = IS_IDENTIFIER_TOKEN;
  return out;
}

// Retruns a list of all of the keys in key_token map
char **getMapKeys() {
  char **out = (char **)malloc(numMapKeys);
  for (int i = 0; i < numMapKeys; i++) {
    *(out + i) = (char *)malloc(sizeof(char) * 15);
  }
  *(out) = OPEN_BRACKET;
  *(out + 1) = CLOSE_BRACKET;
  *(out + 2) = OPEN_PARENTHESIS;
  *(out + 3) = CLOSED_PARENTHESIS;
  *(out + 4) = COMMA;
  *(out + 5) = SEMICOLON;
  *(out + 6) = INTEGER_KEY;
  *(out + 7) = RETURN_KEY;
  *(out + 8) = IS_INTEGER;
  *(out + 9) = IS_IDENTIFIER_KEY;
  return out;
}

// prints the contents of MAP
void printMap(key_tokens *map) {
  char sep[10] = "~~~~~~~~~\n";
  printf("%s", sep);
  for (int i = 0; i < numMapKeys; i++) {
    printf("key = %s\n", (map + i)->key);
    printf("token = %s\n", (map + i)->token);
    printf("isSplit = %d\n", (map + i)->split);
    printf("%s", sep);
  }
}

// gets the token associated with KEY in MAP
char *getToken(char *key, key_tokens *map) {
  for (int i = 0; i < numMapKeys; i++) {
    if (!strcmp(key, (map + i)->key)) {
      return (map + i)->token;
    }
  }
  return "";
}

// Gets the key associated with TOKEN in MAP.
char *getKey(char *token, key_tokens *map) {
  for (int i = 0; i < numMapKeys; i++) {
    if (!strcmp(token, (map + i)->token)) {
      return (map + i)->key;
    }
  }
  return "";
}

// Fill up the map with the built-in c tokens
void fillMap(key_tokens *map) {
  (map)->key = OPEN_BRACKET;
  (map)->token = OPEN_BRACKET_TOCKEN;
  (map)->split = true;

  (map + 1)->key = CLOSE_BRACKET;
  (map + 1)->token = CLOSE_BRACKET_TOKEN;
  (map + 1)->split = false;

  (map + 2)->key = OPEN_PARENTHESIS;
  (map + 2)->token = OPEN_PARENTHESIS_TOKEN;
  (map + 2)->split = true;

  (map + 3)->key = CLOSED_PARENTHESIS;
  (map + 3)->token = CLOSED_PARENTHESIS_TOKEN;
  (map + 3)->split = true;

  (map + 4)->key = COMMA;
  (map + 4)->token = COMMA_KEY;
  (map + 4)->split = true;

  (map + 5)->key = SEMICOLON;
  (map + 5)->token = SEMICOLON_TOKEN;
  (map + 5)->split = false;

  (map + 6)->key = INTEGER_KEY;
  (map + 6)->token = INTEGER_KEY_TOKEN;
  (map + 6)->split = false;

  (map + 7)->key = RETURN_KEY;
  (map + 7)->token = RETURN_KEY_TOKEN;
  (map + 7)->split = false;

  (map + 8)->key = IS_INTEGER;
  (map + 8)->token = IS_INTEGER_TOKEN;
  (map + 8)->split = false;

  (map + 9)->key = IS_IDENTIFIER_KEY;
  (map + 9)->token = IS_IDENTIFIER_TOKEN;
  (map + 9)->split = false;
}

/*
Building the token map with all of the built-in c tokens.
Going to allocate space for 50 characters. All of our keys should be < 10 chars,
and their identifiers should all be less than 38 (2 null spaces for both
strings)
*/
key_tokens *buildMap() {
  int stringSize = sizeof(char) * 50;
  int dataSize = numMapKeys * stringSize;
  key_tokens *map = (key_tokens *)malloc(sizeof(key_tokens) + dataSize);
  fillMap(map);
  return map;
}
