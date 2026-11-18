int get_max_freq(int *array, int size){
  int max_val = 0;
  int max_freq = array[0];
  int i = 0;
  for (i = 0; i < size; i++) {
    int occurence = 0;
    int j = 0;
    for (j = 0; j < size; j++) {
      if (array[j] == array[i]) {
        occurence++;
      }
    }
    if (occurence > max_val) {
      max_val = occurence;
      max_freq = array[i];
    }
  }
  return max_freq;
}