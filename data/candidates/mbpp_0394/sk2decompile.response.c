bool _is_unique(int *array, int size) {
  bool is_unique = true;
  int unique_array[size];
  int unique_array_size = 0;
  for (int i = 0; i < size; i++) {
    int current_value = array[i];
    bool is_duplicate = false;
    for (int j = 0; j < unique_array_size; j++) {
      if (unique_array[j] == current_value) {
        is_duplicate = true;
        break;
      }
    }
    if (is_duplicate) {
      is_unique = false;
      break;
    }
    unique_array[unique_array_size++] = current_value;
  }
  return is_unique;
}