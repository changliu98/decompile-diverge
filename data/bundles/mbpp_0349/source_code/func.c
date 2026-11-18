

#include <stdio.h>

#include <string.h>

#include <assert.h>



char* func0(char* string) {
  int has0 = 0;
  int has1 = 0;
  int hasOther = 0;
  for (int i = 0; i < strlen(string); i++) {
    if (string[i] == '0') {
      has0 = 1;
    } else if (string[i] == '1') {
      has1 = 1;
    } else {
      hasOther = 1;
      break;
    }
  }
  if ((has0 || has1) && !hasOther) {
    return "Yes";
  } else {
    return "No";
  }
}
