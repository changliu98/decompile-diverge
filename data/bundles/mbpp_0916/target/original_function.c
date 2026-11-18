bool func0(int A[], int arr_size, int sum, int* triplet) {
  for (int i = 0; i < arr_size - 2; i++) {
    for (int j = i + 1; j < arr_size - 1; j++) {
      for (int k = j + 1; k < arr_size; k++) {
        if (A[i] + A[j] + A[k] == sum) {
          triplet[0] = A[i];
          triplet[1] = A[j];
          triplet[2] = A[k];
          return true;
        }
      }
    }
  }
  return false;
}