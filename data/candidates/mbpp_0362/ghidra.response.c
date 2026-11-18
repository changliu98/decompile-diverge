int func0(int *nums,int size)

{
  int j;
  int occu;
  int i;
  int result;
  int max_val;
  int size_local;
  int *nums_local;
  
  max_val = 0;
  result = *nums;
  for (i = 0; i < size; i = i + 1) {
    occu = 0;
    for (j = 0; j < size; j = j + 1) {
      if (nums[j] == nums[i]) {
        occu = occu + 1;
      }
    }
    if (max_val < occu) {
      max_val = occu;
      result = nums[i];
    }
  }
  return result;
}