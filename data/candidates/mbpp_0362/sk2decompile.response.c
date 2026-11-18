int _get_most_frequent_number(int* array, int size) {
  int count, i, j, max = 0;
  int most_frequent_number = array[0];
  for (j = 0; j < size; j++) {
    count = 0;
    for (i = 0; i < size; i++) {
      if (array[i] == array[j]) {
        count++;
      }
    }
    if (count > max) {
      max = count;
      most_frequent_number = array[j];
    }
  }
  return most_frequent_number;
}