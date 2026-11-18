bool func0(int* A, int ASize) {
  for (int i = 0; i < ASize; i++) {
    if (A[i] % 2 != i % 2) {
      return false;
    }
  }
  return true;
}