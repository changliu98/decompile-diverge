void addItemToBag(int *item, int *bag, int size) {
  int i;
  for (i = 0; i < size; i++) {
    bag[i] -= item[i];
  }
}