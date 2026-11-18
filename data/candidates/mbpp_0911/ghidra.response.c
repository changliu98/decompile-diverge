int func0(int *nums,int size)

{
  int iVar1;
  int local_48;
  int product2;
  int product1;
  int second_lowest;
  int lowest;
  int third_highest;
  int second_highest;
  int highest;
  int temp;
  int j;
  int i;
  int size_local;
  int *nums_local;
  int local_c;
  
  if (size < 3) {
    local_c = -1;
  }
  else {
    for (i = 0; j = i, i < size + -1; i = i + 1) {
      while (j = j + 1, j < size) {
        if (nums[i] < nums[j]) {
          iVar1 = nums[i];
          nums[i] = nums[j];
          nums[j] = iVar1;
        }
      }
    }
    iVar1 = *nums * nums[1] * nums[2];
    local_48 = *nums * nums[size + -1] * nums[size + -2];
    if (local_48 < iVar1) {
      local_48 = iVar1;
    }
    local_c = local_48;
  }
  return local_c;
}