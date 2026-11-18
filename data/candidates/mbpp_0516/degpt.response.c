void func0(int *nums,int size)

{
  void *__ptr;
  void *__ptr_00;
  long lVar1;
  int iVar2;
  int i_5;
  int index_1;
  int i_4;
  int i_3;
  int index;
  int i_2;
  int i_1;
  int *count;
  int *output;
  int i;
  int max_digit;
  int placement;
  int size_local;
  int *nums_local;
  
  placement = 1;
  max_digit = *nums;
  for (i = 1; i < size; i = i + 1) {
    if (max_digit < nums[i]) {
      max_digit = nums[i];
    }
  }
  __ptr = malloc((long)size << 2);
  __ptr_00 = malloc(0x28);
  for (; placement <= max_digit; placement = placement * 10) {
    for (i_1 = 0; i_1 < 10; i_1 = i_1 + 1) {
      *(undefined4 *)((long)__ptr_00 + (long)i_1 * 4) = 0;
    }
    for (i_2 = 0; i_2 < size; i_2 = i_2 + 1) {
      lVar1 = (long)(int)((long)((ulong)(uint)((int)((long)nums[i_2] / (long)placement) >> 0x1f) <<
                                 0x20 | (long)nums[i_2] / (long)placement & 0xffffffffU) % 10);
      *(int *)((long)__ptr_00 + lVar1 * 4) = *(int *)((long)__ptr_00 + lVar1 * 4) + 1;
    }
    for (i_3 = 1; i_4 = size, i_3 < 10; i_3 = i_3 + 1) {
      *(int *)((long)__ptr_00 + (long)i_3 * 4) =
           *(int *)((long)__ptr_00 + (long)(i_3 + -1) * 4) +
           *(int *)((long)__ptr_00 + (long)i_3 * 4);
    }
    while (i_4 = i_4 + -1, -1 < i_4) {
      iVar2 = (int)((long)((ulong)(uint)((int)((long)nums[i_4] / (long)placement) >> 0x1f) << 0x20 |
                          (long)nums[i_4] / (long)placement & 0xffffffffU) % 10);
      *(int *)((long)__ptr + (long)(*(int *)((long)__ptr_00 + (long)iVar2 * 4) + -1) * 4) =
           nums[i_4];
      *(int *)((long)__ptr_00 + (long)iVar2 * 4) = *(int *)((long)__ptr_00 + (long)iVar2 * 4) + -1;
    }
    for (i_5 = 0; i_5 < size; i_5 = i_5 + 1) {
      nums[i_5] = *(int *)((long)__ptr + (long)i_5 * 4);
    }
  }
  free(__ptr);
  free(__ptr_00);
  return;
}