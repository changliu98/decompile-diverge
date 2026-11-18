int * func0(int *nums,int size)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  void *__ptr;
  size_t sVar4;
  int j_1;
  int i_1;
  int m;
  int j;
  int length;
  int sum;
  char w [12];
  int i;
  int *sumdigit;
  int size_local;
  int *nums_local;
  
  __ptr = malloc((long)size << 2);
  for (i = 0; i < size; i = i + 1) {
    uVar2 = abs(nums[i]);
    sprintf(w,"%d",(ulong)uVar2);
    sum = 0;
    sVar4 = strlen(w);
    for (j = 1; j < (int)sVar4; j = j + 1) {
      sum = w[j] + -0x30 + sum;
    }
    if (nums[i] < 1) {
      iVar3 = -(w[0] + -0x30);
    }
    else {
      iVar3 = w[0] + -0x30;
    }
    sum = iVar3 + sum;
    *(int *)((long)__ptr + (long)i * 4) = sum;
  }
  for (i_1 = 0; i_1 < size; i_1 = i_1 + 1) {
    for (j_1 = 1; j_1 < size; j_1 = j_1 + 1) {
      if (*(int *)((long)__ptr + (long)j_1 * 4) < *(int *)((long)__ptr + (long)(j_1 + -1) * 4)) {
        uVar1 = *(undefined4 *)((long)__ptr + (long)j_1 * 4);
        *(undefined4 *)((long)__ptr + (long)j_1 * 4) =
             *(undefined4 *)((long)__ptr + (long)(j_1 + -1) * 4);
        *(undefined4 *)((long)__ptr + (long)(j_1 + -1) * 4) = uVar1;
        iVar3 = nums[j_1];
        nums[j_1] = nums[j_1 + -1];
        nums[j_1 + -1] = iVar3;
      }
    }
  }
  free(__ptr);
  return nums;
}