long long _get_num_of_combinations(int n, int r) {
  long long num_of_combinations;
  num_of_combinations = (long long)pow((double)(n - r + 1), 3.0);
  return num_of_combinations;
}