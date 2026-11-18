

#include <assert.h>



int func0(int A[], int n) {
  if (n == 1) {
    return A[0];
  }
  int look_up[n];
  look_up[0] = A[0];
  look_up[1] = A[0] > A[1] ? A[0] : A[1];
  for (int i = 2; i < n; i++) {
    int option1 = look_up[i - 1];
    int option2 = look_up[i - 2] + A[i];
    int option3 = A[i];
    look_up[i] = option1 > option2 ? option1 : option2;
    look_up[i] = look_up[i] > option3 ? look_up[i] : option3;
  }
  return look_up[n - 1];
}
