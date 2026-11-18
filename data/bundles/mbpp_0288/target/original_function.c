int func0(int arr[], int N, int P) {
  int current_element = 0;
  for (int i = 0; i < N; i++) {
    if ((arr[i] * arr[i]) % P == 1) {
      current_element += 1;
    }
  }
  return current_element;
}