void shift_array(char *array) {
  int i;
  for (i = 0; array[i] != '\0'; i++) {
    array[i] += 5;
  }
}