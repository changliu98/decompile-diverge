

#include <stdio.h>

#include <string.h>

#include <assert.h>



int check_Equality(char *s, int start, int length) {

    return (s[start] == s[start + length - 1]);

}



int func0(char *s) {
  int result = 0;
  int n = strlen(s);
  for (int i = 0; i < n; i++) {
    for (int j = 1; j <= n - i; j++) {
      if (check_Equality(s, i, j)) {
        result++;
      }
    }
  }
  return result;
}
