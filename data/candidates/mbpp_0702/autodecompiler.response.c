int func0(int *a, int n, int k) {
  int pivot, start, end, min, ind;
  int len = n-1;

  qsort__bench(a, (size_t)n, sizeof(int), compar);

  start = 0;
  while (1) {
    if (start >= n) break;

    ind = find_ind(a[start], start, n, k, a);
    if (ind != -1) {
      if (len > (n-(ind-start+1))) {
        min = len;
      } else {
        min = n-(ind-start+1);
      }
      len = min;
    }

    start++;
  }

  return len;
}