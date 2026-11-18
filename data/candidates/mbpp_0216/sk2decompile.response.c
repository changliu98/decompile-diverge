bool _check_all_in_array(int *array, int array_size, int *check_array,
                         int check_array_size) {
  bool result = true;
  for (int i = 0; i < check_array_size; i++) {
    bool found = false;
    for (int j = 0; j < array_size; j++) {
      if (check_array[i] == array[j]) {
        found = true;
        break;
      }
    }
    if (!found) {
      result = false;
      break;
    }
  }
  return result;
}