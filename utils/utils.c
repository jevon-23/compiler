#include "utils.h"
#include <ctype.h>
#include <float.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 10000

// source : https://pubs.opengroup.org/onlinepubs/7908799/xsh/regcomp.html
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

// If we run into an error, return a message and exit program.
void error(int code) {
  switch (code) {
  case 0: // Invalid .extension
    printf("Invalid file type. We want this to work for .py, .java, .c, and "
           ".golang sometime in the future, but a sof rn only .c files are "
           "available");
  default:
    printf("Something went wrong");
  }
  exit(-1);
}

// Print a seperator
void printSpace() {
  printf("\n~~~~~~~~~~~~~~~~~~~~~~~~");
  printf("\n");
}

/*
Reads the contents of theFile.
*/
void readContents(aFile theFile) {
  for (int i = 0; i < theFile.lineCount; i++) {
    printf("%s", (*(theFile.contents + i)));
  }
}

/*
Removes the indentation of the contents by shifting all values as far left as
possible
*/
void formatString(aFile *theFile, int lineInd, int startInd) {
  *(theFile->contents + lineInd) += startInd; // shift the string over
}

/*
 Removes the indentations of theFiles' contents
*/
void formatFile(aFile *theFile) {

  for (int i = 0; i < theFile->lineCount; i++) {
    for (int j = 0; j < strlen(*(theFile->contents + i)); j++) {
      // Once we find our first non-whitespace value
      if (!isspace(*(*(theFile->contents + i) + j))) {

        formatString(theFile, i, j);
        break;
      }
    }
  }
}

/*
Reads the file, stores the name and its contents inside a AFILE struct
*/
aFile readFile(char *fileName) {
  // Opening the file that we are reading
  FILE *currFile = fopen(fileName, "r");
  if (currFile == NULL) {
    error(1);
  }

  // Creating a new afile instance. Making room for the first line to be read
  // from file
  aFile theFile;
  theFile.name = fileName;
  theFile.contents =
      (char **)malloc(sizeof(char *)); // The content that fileName holds
  *theFile.contents = (char *)malloc(sizeof(char) * MAX_LINE_LEN);
  theFile.lineCount = 0;

  // Read this line from the file, and storing it at a value inside of
  // theContents
  for (int i = 0; fgets(*(theFile.contents + i), MAX_LINE_LEN, currFile); i++) {

    // Create space for the next line of code
    theFile.contents = (char **)realloc(theFile.contents, i + 1);
    *(theFile.contents + i + 1) = (char *)malloc(sizeof(char) * MAX_LINE_LEN);
    theFile.lineCount++;
  }
  fclose(currFile);
  formatFile(&theFile);
  printf("read %s\n", fileName);
  return theFile;
}
