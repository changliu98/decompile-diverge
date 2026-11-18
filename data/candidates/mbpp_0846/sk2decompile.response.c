int func0(int *start, int *end, int n) {
  qsort(start, n, sizeof(start[0]), cmp);
  qsort(end, n, sizeof(end[0]), cmp);
  int count = 1, max = 1, i = 1, j = 0;
  while (i < n && j < n) {
    if (start[i] <= end[j]) {
      count++;
      i++;
      if (count > max) max = count;
    } else {
      count--;
      j++;
    }
  }
  return max;
}