#include <stdbool.h>
/*
Just a mapping between the name of a file and the contents that file holds just
to make my life a little easier in the future Going to make all of these, the
head of the list will always be the the file that we are running search on
*/

#ifndef UTILS_H // header guard
#define UTILS_H

typedef struct aFile {
  char *name;      // Name of file
  char **contents; // Contents in file
  int lineCount;   // How long is the file
} aFile;

aFile readFile(char *fileName);
void formatFile(aFile *theFile);
void readContents(aFile theFile);
void printSpace();
bool match(const char *string, char *pattern);

#endif // PARSER_H
