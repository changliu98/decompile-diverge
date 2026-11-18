

#include <stdio.h>

#include <stdlib.h>

#include <assert.h>



int cmpfunc(const void *a, const void *b) {

    return (*(int*)a - *(int*)b);

}



int func0(int arr[], int N, int K) {
  qsort(arr, N, sizeof(int), cmpfunc);
  int *dp = (int *)malloc(N * sizeof(int));
  dp[0] = 0;
  for (int i = 1; i < N; i++) {
    dp[i] = dp[i - 1];
    if (arr[i] - arr[i - 1] < K) {
      if (i >= 2) {
        dp[i] = (dp[i] > (dp[i - 2] + arr[i] + arr[i - 1]))
                    ? dp[i]
                    : (dp[i - 2] + arr[i] + arr[i - 1]);
      } else {
        dp[i] = (dp[i] > (arr[i] + arr[i - 1])) ? dp[i] : (arr[i] + arr[i - 1]);
      }
    }
  }
  int result = dp[N - 1];
  free(dp);
  return result;
}
