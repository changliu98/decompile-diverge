int func0(int *arr,int n)

{
  int *piVar1;
  int local_48 [3];
  int i_2;
  int maxVal;
  int j;
  int i_1;
  int i;
  unsigned_long __vla_expr0;
  int n_local;
  int *arr_local;
  
                    /* Unresolved local var: int[201] mpis@[???] */
  piVar1 = (int *)((long)local_48 - ((ulong)(uint)n * 4 + 0xf & 0xfffffffffffffff0));
  for (i = 0; i < n; i = i + 1) {
    piVar1[i] = arr[i];
  }
  for (i_1 = 1; i_1 < n; i_1 = i_1 + 1) {
    for (j = 0; j < i_1; j = j + 1) {
      if ((arr[j] < arr[i_1]) && (piVar1[i_1] < piVar1[j] * arr[i_1])) {
        piVar1[i_1] = piVar1[j] * arr[i_1];
      }
    }
  }
  maxVal = *piVar1;
  for (i_2 = 1; i_2 < n; i_2 = i_2 + 1) {
    if (maxVal < piVar1[i_2]) {
      maxVal = piVar1[i_2];
    }
  }
  return maxVal;
}