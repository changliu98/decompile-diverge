int check_sorted(int *arr, int len) {
  int i;
  char sorted = 0;

  for (i = 0; !sorted; i++) {
    if (i >= len - 1)
      sorted = 1;
    else if (arr[i] > arr[i + 1])
      break;
  }

  return sorted;
}