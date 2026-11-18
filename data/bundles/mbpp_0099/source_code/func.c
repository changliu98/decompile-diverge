

#include <stdio.h>

#include <assert.h>

#include <string.h>



char* func0(int n) {
  static char binary[32];
  int index = 0;
  while (n > 0) {
    binary[index++] = (n % 2) + '0';
    n /= 2;
  }
  binary[index] = '\0';
  int start = 0;
  int end = index - 1;
  while (start < end) {
    char temp = binary[start];
    binary[start] = binary[end];
    binary[end] = temp;
    start++;
    end--;
  }
  return binary;
}
