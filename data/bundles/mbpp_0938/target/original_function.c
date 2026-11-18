void func0(int A[], int B[], int C[], int p, int q, int r, int res[3]) {
  int diff = INT_MAX;
  int res_i = 0;
  int res_j = 0;
  int res_k = 0;
  int i = 0;
  int j = 0;
  int k = 0;
  while (i < p && j < q && k < r) {
    int minimum =
        A[i] < B[j] ? (A[i] < C[k] ? A[i] : C[k]) : (B[j] < C[k] ? B[j] : C[k]);
    int maximum =
        A[i] > B[j] ? (A[i] > C[k] ? A[i] : C[k]) : (B[j] > C[k] ? B[j] : C[k]);
    if (maximum - minimum < diff) {
      res_i = i;
      res_j = j;
      res_k = k;
      diff = maximum - minimum;
    }
    if (diff == 0) {
      break;
    }
    if (A[i] == minimum) {
      i++;
    } else if (B[j] == minimum) {
      j++;
    } else {
      k++;
    }
  }
  res[0] = A[res_i];
  res[1] = B[res_j];
  res[2] = C[res_k];
}