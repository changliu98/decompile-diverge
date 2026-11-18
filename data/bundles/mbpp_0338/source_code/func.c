

#include <stdio.h>

#include <assert.h>

#include <string.h>



int check_Equality(char* s, int start, int end) {

    return (s[start] == s[end]); 

}



int func0(char* s) {
  int result = 0;
  int n = strlen(s);
  for (int i = 0; i < n; i++) {
    for (int j = 1; j <= n - i; j++) {
      if (check_Equality(s, i, i + j - 1)) {
        result++;
      }
    }
  }
  return result;
}
