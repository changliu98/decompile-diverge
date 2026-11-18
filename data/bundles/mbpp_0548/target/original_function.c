int func0(int arr[], int n) {
  int longest_increasing_subsequence[n];
  for (int i = 0; i < n; i++) {
    longest_increasing_subsequence[i] = 1;
  }
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (arr[i] > arr[j] && longest_increasing_subsequence[i] <
                                 longest_increasing_subsequence[j] + 1) {
        longest_increasing_subsequence[i] =
            longest_increasing_subsequence[j] + 1;
      }
    }
  }
  int maximum = 0;
  for (int i = 0; i < n; i++) {
    if (longest_increasing_subsequence[i] > maximum) {
      maximum = longest_increasing_subsequence[i];
    }
  }
  return maximum;
}