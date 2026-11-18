double func0(int numbers[], int size) {
  int total = 0;
  for (int i = 0; i < size; i++) {
    total += numbers[i];
  }
  return (double)total / size;
}