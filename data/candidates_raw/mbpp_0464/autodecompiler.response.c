int search(int *array, int size, int element) {
  int i = 0;
  char found = 0;

  while (!found && i < size) {
    if (array[i] == element) {
      found = 1;
    }
    i++;
  }

  return found;
}