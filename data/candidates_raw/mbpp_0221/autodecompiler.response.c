int even(int A[], int n) {
  int i;
  int x;

  i = 0;
  while (1) {
    if (i < n) {
      if (A[i] % 2 == 0) {
        x = A[i];
        break;
      }
    } else {
      x = -1;
      break;
    }
    i++;
  }

  return x;
}