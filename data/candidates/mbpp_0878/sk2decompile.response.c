bool _check_all_in_array(int *array, int array_size, int *check_array,
                         int check_array_size) {
  int i, j;
  bool found;
  for (i = 0; i < array_size; i++) {
    found = false;
    for (j = 0; j < check_array_size; j++) {
      if (array[i] == check_array[j]) {
        found = true;
        break;
      }
    }
    if (!found) {
      return false;
    }
  }
  return true;
}