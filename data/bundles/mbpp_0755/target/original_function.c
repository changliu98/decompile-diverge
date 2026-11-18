double func0(double* numbers, int length) {
  if (length < 2) {
    return -9999999;
  }
  int count = 0;
  for (int i = 0; i < length; i++) {
    for (int j = i + 1; j < length; j++) {
      if (numbers[j] == numbers[i]) {
        count += 1;
        break;
      }
    }
  }
  if (length == 2 && count == 1) {
    return -9999999;
  }
  double* uniq_items = malloc(length * sizeof(double));
  int uniq_length = 0;
  for (int i = 0; i < length; i++) {
    int found = 0;
    for (int j = 0; j < uniq_length; j++) {
      if (uniq_items[j] == numbers[i]) {
        found = 1;
        break;
      }
    }
    if (!found) {
      uniq_items[uniq_length++] = numbers[i];
    }
  }
  for (int i = 0; i < uniq_length; i++) {
    for (int j = i + 1; j < uniq_length; j++) {
      if (uniq_items[i] > uniq_items[j]) {
        double temp = uniq_items[i];
        uniq_items[i] = uniq_items[j];
        uniq_items[j] = temp;
      }
    }
  }
  double result = uniq_items[1];
  free(uniq_items);
  return result;
}