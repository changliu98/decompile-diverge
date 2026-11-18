int func0(int arr[], int n) {
  int MSIBS[n];
  for (int i = 0; i < n; i++) {
    MSIBS[i] = arr[i];
  }
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (arr[i] > arr[j] && MSIBS[i] < MSIBS[j] + arr[i]) {
        MSIBS[i] = MSIBS[j] + arr[i];
      }
    }
  }
  int MSDBS[n];
  for (int i = 0; i < n; i++) {
    MSDBS[i] = arr[i];
  }
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (arr[n - i - 1] > arr[n - j - 1] &&
          MSDBS[n - i - 1] < MSDBS[n - j - 1] + arr[n - i - 1]) {
        MSDBS[n - i - 1] = MSDBS[n - j - 1] + arr[n - i - 1];
      }
    }
  }
  int max_sum = -99999999;
  for (int i = 0; i < n; i++) {
    if (max_sum < MSIBS[i] + MSDBS[i] - arr[i]) {
      max_sum = MSIBS[i] + MSDBS[i] - arr[i];
    }
  }
  return max_sum;
}