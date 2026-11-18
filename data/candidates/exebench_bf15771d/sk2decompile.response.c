int computesizes(int *counts, int *n) {
  int size, sum, max, i, j;
  sum = 0;
  max = 0;
  size = 0;
  i = 0;
  j = 1;
  while (j / 2 < *n) {
    if (counts[i] > 0) {
      sum += counts[i];
      if (sum > j / 2) {
        size = j;
        max = sum;
      }
    }
    if (sum == *n) break;
    i++;
    j *= 2;
  }
  *n = size;
  return max;
}