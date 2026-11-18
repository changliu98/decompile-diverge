int _get_num_of_buckets(int** buckets, int num_of_buckets, int num_of_keys,
                        int num_of_values) {
  int i, j, sum, num = 0;
  for (j = 0; j < num_of_buckets; j++) {
    sum = 0;
    for (i = 0; i < num_of_keys; i++) {
      sum += buckets[j][i];
    }
    if (sum > 0) {
      num += (sum + num_of_values - 1) / num_of_values;
    }
  }
  return num;
}