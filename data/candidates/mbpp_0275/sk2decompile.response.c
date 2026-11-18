int _get_max_bucket(int *bucket, int n, int n_bucket) {
  int i, max, max_i;
  for (i = 0; i < n; i++) {
    bucket[i] = bucket[i] / n_bucket + (bucket[i] % n_bucket != 0);
  }
  max = -1;
  max_i = -1;
  for (i = n - 1; i >= 0; i--) {
    if (bucket[i] > max) {
      max = bucket[i];
      max_i = i;
    }
  }
  return max_i + 1;
}