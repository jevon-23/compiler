#include <stdbool.h>
#ifndef KEY_TOKEN_H // header guarde
#define KEY_TOKEN_H

// Key_tkoens, a mapping of the key tokens.
typedef struct key_tokens {
  char *key;
  char *token;
  bool split;
} key_tokens;

// Tokens, Not making this a type so that we do not have to build anything at
// runtime. Might change this but will have to have this background regardless
#define OPEN_BRACKET "{"
#define OPEN_BRACKET_TOCKEN "open_bracket" // {
#define CLOSE_BRACKET "}"
#define CLOSE_BRACKET_TOKEN "close_bracket" // }
#define OPEN_PARENTHESIS "("
#define OPEN_PARENTHESIS_TOKEN "open_parenthesis" // (
#define CLOSED_PARENTHESIS ")"
#define CLOSED_PARENTHESIS_TOKEN "closed_parenthesis" // )
#define COMMA ","
#define COMMA_KEY "comma"
#define SEMICOLON ";\0"
#define SEMICOLON_TOKEN "semi_colon" // ;
#define INTEGER_KEY "int"
#define INTEGER_KEY_TOKEN "int_key" // int
#define RETURN_KEY "return"
#define RETURN_KEY_TOKEN "ret_key" // return
#define IS_INTEGER "[:digit:]+"
#define IS_INTEGER_TOKEN "is_int" // [0-9]+
#define IS_IDENTIFIER_KEY "[_[:alnum:]]"
#define IS_IDENTIFIER_TOKEN "identifier"

// Functions
key_tokens *buildMap(); // Build  a mapping of all keys -> tokens
char *getToken(char *key, key_tokens *map); // Get the token associated with key
char *getKey(char *token, key_tokens *map); // Get the key associated with token
void printMap(key_tokens *map); // Print the mapp of all keys (mainly for
char **getMapKeys();            // Return a list of all of the keys in the list
char **getMapTokens(); // Returns a list of all of the tokens in the list
#endif
