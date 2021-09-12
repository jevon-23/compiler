#include "../key_token.h"
#include <float.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void TestGetMapTokens() {
  char **mapTokens = getMapTokens();
  for (int i = 0; i < 10; i++) {
    printf("token %d = %s\n", i, *(mapTokens + i));
  }
}

void TestGetMapKeys() {
  char **mapKeys = getMapKeys();
  for (int i = 0; i < 10; i++) {
    printf("key %d = %s\n", i, *(mapKeys + i));
  }
}

void TestGetKey() {
  printf("TestGetKey; token = %s\n", RETURN_KEY_TOKEN);
  key_tokens *map = buildMap();
  char *key = getKey(RETURN_KEY_TOKEN, map);
  printf("key = %s\n", key);
}

void TestGetToken() {
  printf("TestGetToken; key = %s\n", COMMA);
  key_tokens *map = buildMap();
  char *token = getToken(COMMA, map);
  printf("token = %s\n", token);
}

void TestBuildMap() {
  key_tokens *map = buildMap();
  printMap(map);
}

int main(int arg, char *argv[]) {
  // TestBuildMap();
  // TestGetToken();
  // TestGetKey();
  // TestGetMapKeys();
  TestGetMapTokens();
}
