int func0(int *arr, int n) {
  int lcm = find_lcm(arr[0], arr[1]);
  int i;
  for (i = 2; i < n; i++) {
    lcm = find_lcm(lcm, arr[i]);
  }
  return lcm;
}