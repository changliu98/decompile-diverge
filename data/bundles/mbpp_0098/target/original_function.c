double func0(int numbers[], int size) {
  double total = 1;
  for (int i = 0; i < size; i++) {
    total *= numbers[i];
  }
  return total / size;
}