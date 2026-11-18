int func0(int *arr,int n)

{
  long lVar1;
  int aiStack_48 [4];
  int i_2;
  int j;
  int i_1;
  int i;
  unsigned_long __vla_expr0;
  int max;
  int n_local;
  int *arr_local;
  
                    /* Unresolved local var: int[212] msis@[???] */
  max = 0;
  lVar1 = -0x48 - ((ulong)(uint)n * 4 + 0xf & 0xfffffffffffffff0);
  for (i = 0; i < n; i = i + 1) {
    *(int *)((long)aiStack_48 + (long)i * 4 + lVar1 + 0x48) = arr[i];
  }
  for (i_1 = 1; i_1 < n; i_1 = i_1 + 1) {
    for (j = 0; j < i_1; j = j + 1) {
      if ((arr[j] < arr[i_1]) &&
         (*(int *)((long)aiStack_48 + (long)i_1 * 4 + lVar1 + 0x48) <
          *(int *)((long)aiStack_48 + (long)j * 4 + lVar1 + 0x48) + arr[i_1])) {
        *(int *)((long)aiStack_48 + (long)i_1 * 4 + lVar1 + 0x48) =
             *(int *)((long)aiStack_48 + (long)j * 4 + lVar1 + 0x48) + arr[i_1];
      }
    }
  }
  for (i_2 = 0; i_2 < n; i_2 = i_2 + 1) {
    if (max < *(int *)((long)aiStack_48 + (long)i_2 * 4 + lVar1 + 0x48)) {
      max = *(int *)((long)aiStack_48 + (long)i_2 * 4 + lVar1 + 0x48);
    }
  }
  return max;
}