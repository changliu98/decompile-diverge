int func0(int *arr,int n)

{
  long lVar1;
  long lVar2;
  int local_68 [5];
  int i_4;
  int max_sum;
  int j_1;
  int i_3;
  int i_2;
  unsigned_long __vla_expr1;
  int j;
  int i_1;
  int i;
  unsigned_long __vla_expr0;
  int n_local;
  int *arr_local;
  
                    /* Unresolved local var: int[201] MSIBS@[???]
                       Unresolved local var: int[210] MSDBS@[???] */
  lVar1 = -0x68 - ((ulong)(uint)n * 4 + 0xf & 0xfffffffffffffff0);
  for (i = 0; i < n; i = i + 1) {
    *(int *)((long)local_68 + (long)i * 4 + lVar1 + 0x68) = arr[i];
  }
  for (i_1 = 1; i_1 < n; i_1 = i_1 + 1) {
    for (j = 0; j < i_1; j = j + 1) {
      if ((arr[j] < arr[i_1]) &&
         (*(int *)((long)local_68 + (long)i_1 * 4 + lVar1 + 0x68) <
          *(int *)((long)local_68 + (long)j * 4 + lVar1 + 0x68) + arr[i_1])) {
        *(int *)((long)local_68 + (long)i_1 * 4 + lVar1 + 0x68) =
             *(int *)((long)local_68 + (long)j * 4 + lVar1 + 0x68) + arr[i_1];
      }
    }
  }
  lVar2 = lVar1 - ((ulong)(uint)n * 4 + 0xf & 0xfffffffffffffff0);
  for (i_2 = 0; i_2 < n; i_2 = i_2 + 1) {
    *(int *)((long)local_68 + (long)i_2 * 4 + lVar2 + 0x68) = arr[i_2];
  }
  for (i_3 = 1; i_3 < n; i_3 = i_3 + 1) {
    for (j_1 = 0; j_1 < i_3; j_1 = j_1 + 1) {
      if ((arr[(n - j_1) + -1] < arr[(n - i_3) + -1]) &&
         (*(int *)((long)local_68 + (long)((n - i_3) + -1) * 4 + lVar2 + 0x68) <
          *(int *)((long)local_68 + (long)((n - j_1) + -1) * 4 + lVar2 + 0x68) + arr[(n - i_3) + -1]
         )) {
        *(int *)((long)local_68 + (long)((n - i_3) + -1) * 4 + lVar2 + 0x68) =
             *(int *)((long)local_68 + (long)((n - j_1) + -1) * 4 + lVar2 + 0x68) +
             arr[(n - i_3) + -1];
      }
    }
  }
  max_sum = -99999999;
  for (i_4 = 0; i_4 < n; i_4 = i_4 + 1) {
    if (max_sum < (*(int *)((long)local_68 + (long)i_4 * 4 + lVar1 + 0x68) +
                  *(int *)((long)local_68 + (long)i_4 * 4 + lVar2 + 0x68)) - arr[i_4]) {
      max_sum = (*(int *)((long)local_68 + (long)i_4 * 4 + lVar1 + 0x68) +
                *(int *)((long)local_68 + (long)i_4 * 4 + lVar2 + 0x68)) - arr[i_4];
    }
  }
  return max_sum;
}