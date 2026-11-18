int func0(int nums[], int size) {
  int max_val = 0;
  int result = nums[0];
  for (int i = 0; i < size; i++) {
    int occu = 0;
    for (int j = 0; j < size; j++) {
      if (nums[j] == nums[i]) {
        occu++;
      }
    }
    if (occu > max_val) {
      max_val = occu;
      result = nums[i];
    }
  }
  return result;
}