bool _is_in_array(int *array, int size, int value) {
  bool ret = false;
  int i;
  for (i = 0; i < size; i++) {
    if (array[i] == value) {
      ret = true;
      break;
    }
  }
  return ret;
}