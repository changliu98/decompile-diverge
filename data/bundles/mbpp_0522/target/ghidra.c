int func0(int *arr,int n)

{
  int *piVar1;
  int *piVar2;
  int aiStack_58 [7];
  int maximum;
  int j;
  int i;
  unsigned_long __vla_expr1;
  unsigned_long __vla_expr0;
  int n_local;
  int *arr_local;
  
                    /* Unresolved local var: int[201] lis@[???]
                       Unresolved local var: int[210] lds@[???] */
  piVar1 = (int *)((long)aiStack_58 - ((ulong)(n + 1) * 4 + 0xf & 0xfffffffffffffff0));
  piVar2 = (int *)((long)piVar1 - ((ulong)(n + 1) * 4 + 0xf & 0xfffffffffffffff0));
  for (i = 0; i <= n; i = i + 1) {
    piVar1[i] = 1;
  }
  for (i = 1; i < n; i = i + 1) {
    for (j = 0; j < i; j = j + 1) {
      if ((arr[j] < arr[i]) && (piVar1[i] < piVar1[j] + 1)) {
        piVar1[i] = piVar1[j] + 1;
      }
    }
  }
  for (i = 0; i <= n; i = i + 1) {
    piVar2[i] = 1;
  }
  for (i = n + -2; j = n, -1 < i; i = i + -1) {
    while (j = j + -1, i < j) {
      if ((arr[j] < arr[i]) && (piVar2[i] < piVar2[j] + 1)) {
        piVar2[i] = piVar2[j] + 1;
      }
    }
  }
  maximum = *piVar1 + *piVar2 + -1;
  for (i = 1; i < n; i = i + 1) {
    if (maximum < piVar1[i] + piVar2[i] + -1) {
      maximum = piVar1[i] + piVar2[i] + -1;
    }
  }
  return maximum;
}