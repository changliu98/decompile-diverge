void func0(int my_list[], int length) {
  int gap = length / 2;
  while (gap > 0) {
    for (int i = gap; i < length; i++) {
      int current_item = my_list[i];
      int j = i;
      while (j >= gap && my_list[j - gap] > current_item) {
        my_list[j] = my_list[j - gap];
        j -= gap;
      }
      my_list[j] = current_item;
    }
    gap /= 2;
  }
}