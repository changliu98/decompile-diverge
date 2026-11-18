char* func0(int arr[], int n, int p) {
  int _sum = 0;
  for (int i = 0; i < n; i++) {
    _sum += arr[i];
  }
  if (p == 1) {
    if (_sum % 2 == 0) {
      return "ODD";
    } else {
      return "EVEN";
    }
  }
  return "EVEN";
}