

#include <assert.h>

#include <stdio.h>

#include <stdlib.h>



unsigned long long func0(int n) {
  unsigned long long** bell = malloc((n + 1) * sizeof(unsigned long long*));
  for (int i = 0; i <= n; i++) {
    bell[i] = malloc((n + 1) * sizeof(unsigned long long));
    for (int j = 0; j <= n; j++) {
      bell[i][j] = 0;
    }
  }
  bell[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    bell[i][0] = bell[i - 1][i - 1];
    for (int j = 1; j <= i; j++) {
      bell[i][j] = bell[i - 1][j - 1] + bell[i][j - 1];
    }
  }
  unsigned long long result = bell[n][0];
  for (int i = 0; i <= n; i++) {
    free(bell[i]);
  }
  free(bell);
  return result;
}
