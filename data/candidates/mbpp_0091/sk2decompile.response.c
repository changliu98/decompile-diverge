bool _is_in_array(char **array, char *str, int size) {
  int i;
  for (i = 0; i < size; i++) {
    if (strstr(array[i], str) != NULL) {
      return true;
    }
  }
  return false;
}