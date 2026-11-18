

#include <stdio.h>

#include <assert.h>

#include <limits.h>

#include <string.h>



int func0(int num) {
  for (int i = num + 1; i < INT_MAX; i++) {
    char numstr[20];
    sprintf(numstr, "%d", i);
    int len = strlen(numstr);
    int isPalindrome = 1;
    for (int j = 0; j < len / 2; j++) {
      if (numstr[j] != numstr[len - 1 - j]) {
        isPalindrome = 0;
        break;
      }
    }
    if (isPalindrome) {
      return i;
    }
  }
  return -1;
}
