int func0(int A[], int n) {
  int i, j, temp;
  for (i = 0; i < n; i++) {
    for (j = i + 1; j < n; j++) {
      if (A[i] > A[j]) {
        temp = A[j];
        A[j] = A[i];
        A[i] = temp;
      }
    }
  }
  for (i = n - 1; i >= 0; i--) {
    if (is_palindrome(A[i])) {
      return A[i];
    }
  }
  return -1;
}