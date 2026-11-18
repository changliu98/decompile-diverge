void _shell_sort(int *array, int size) {
  int gap = size;
  int swapped = 1;
  int i;
  int temp;
  while (gap > 1 || swapped) {
    if (gap > 1) {
      gap = (int)((float)gap / 1.3);
    }
    swapped = 0;
    for (i = 0; i + gap < size; i++) {
      if (array[i] > array[i + gap]) {
        temp = array[i];
        array[i] = array[i + gap];
        array[i + gap] = temp;
        swapped = 1;
      }
    }
  }
}