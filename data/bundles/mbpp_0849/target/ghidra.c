int func0(int N)

{
  long lVar1;
  int local_38 [3];
  int j;
  int i_1;
  int i;
  unsigned_long __vla_expr0;
  int N_local;
  
                    /* Unresolved local var: int[177] SumOfPrimeDivisors@[???] */
  lVar1 = -0x38 - ((ulong)(N + 1) * 4 + 0xf & 0xfffffffffffffff0);
  for (i = 0; i <= N; i = i + 1) {
    *(undefined4 *)((long)local_38 + (long)i * 4 + lVar1 + 0x38) = 0;
  }
  for (i_1 = 2; i_1 <= N; i_1 = i_1 + 1) {
    if (*(int *)((long)local_38 + (long)i_1 * 4 + lVar1 + 0x38) == 0) {
      for (j = i_1; j <= N; j = i_1 + j) {
        *(int *)((long)local_38 + (long)j * 4 + lVar1 + 0x38) =
             i_1 + *(int *)((long)local_38 + (long)j * 4 + lVar1 + 0x38);
      }
    }
  }
  return *(int *)((long)local_38 + (long)N * 4 + lVar1 + 0x38);
}