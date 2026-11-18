void decrement_value(int *value) {
  if (value == NULL) {
    return;
  }
  *value = *value - 1;
}