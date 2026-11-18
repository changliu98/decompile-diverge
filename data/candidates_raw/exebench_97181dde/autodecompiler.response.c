void set(int *array, int index) {
  int array_index = index / (sizeof(int)*8);
  int bit = index % (sizeof(int)*8);
  int mask = 1 << bit;
  array[array_index] |= mask;
}