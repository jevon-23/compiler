#include "../utils.h"
#include <float.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void TestReadFile() {
  aFile theFile = readFile("basic.c");
  readContents(theFile);
}

void TestFormatFile() {
  aFile basic = readFile("basic.c");
  formatFile(&basic);
  readContents(basic);
}

int main() {
  TestReadFile();
  printSpace();
  TestFormatFile();
}
