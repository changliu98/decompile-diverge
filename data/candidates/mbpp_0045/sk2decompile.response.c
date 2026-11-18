int func0(int *arr, int n) {
  int gcd = find_gcd(arr[0], arr[1]);
  int i;
  for (i = 2; i < n; i++) {
    gcd = find_gcd(gcd, arr[i]);
  }
  return gcd;
}