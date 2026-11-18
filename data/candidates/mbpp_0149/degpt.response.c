int func0(int *arr,int n)

{
  long lVar1;
  int local_48 [3];
  int i_2;
  int result;
  int j;
  int i_1;
  int i;
  unsigned_long __vla_expr0;
  int n_local;
  int *arr_local;
  
                    /* Unresolved local var: int[201] dp@[???] */
  lVar1 = -0x48 - ((ulong)(uint)n * 4 + 0xf & 0xfffffffffffffff0);
  for (i = 0; i < n; i = i + 1) {
    *(undefined4 *)((long)local_48 + (long)i * 4 + lVar1 + 0x48) = 1;
  }
  for (i_1 = 0; i_1 < n; i_1 = i_1 + 1) {
    for (j = 0; j < i_1; j = j + 1) {
      if (((arr[i_1] == arr[j] + 1) || (arr[i_1] == arr[j] + -1)) &&
         (*(int *)((long)local_48 + (long)i_1 * 4 + lVar1 + 0x48) <
          *(int *)((long)local_48 + (long)j * 4 + lVar1 + 0x48) + 1)) {
        *(int *)((long)local_48 + (long)i_1 * 4 + lVar1 + 0x48) =
             *(int *)((long)local_48 + (long)j * 4 + lVar1 + 0x48) + 1;
      }
    }
  }
  result = 1;
  for (i_2 = 0; i_2 < n; i_2 = i_2 + 1) {
    if (result < *(int *)((long)local_48 + (long)i_2 * 4 + lVar1 + 0x48)) {
      result = *(int *)((long)local_48 + (long)i_2 * 4 + lVar1 + 0x48);
    }
  }
  return result;
}