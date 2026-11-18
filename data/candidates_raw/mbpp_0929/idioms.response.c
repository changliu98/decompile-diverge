int count(int *tuplex, int size, int value){
  int count = 0;
  int i = 0;
  for (i = 0; i < size; i++) {
    if (tuplex[i] == value) {
      count++;
    }
  }
  return count;
}