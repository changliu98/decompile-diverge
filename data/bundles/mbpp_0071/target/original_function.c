void func0(int *nums, int size) {
  float shrink_fact = 1.3;
  int gaps = size;
  int swapped = 1;
  int i = 0;
  while (gaps > 1 || swapped) {
    gaps = (int)((float)gaps / shrink_fact);
    swapped = 0;
    i = 0;
    while (gaps + i < size) {
      if (nums[i] > nums[i + gaps]) {
        int temp = nums[i];
        nums[i] = nums[i + gaps];
        nums[i + gaps] = temp;
        swapped = 1;
      }
      i++;
    }
  }
}