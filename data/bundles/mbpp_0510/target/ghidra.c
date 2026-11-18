int func0(int *arr,int n,int k)

{
  long lVar1;
  long lVar2;
  ulong uVar3;
  int aiStack_58 [6];
  int j_1;
  int i_1;
  int j;
  int i;
  unsigned_long __vla_expr1;
  unsigned_long __vla_expr0;
  int k_local;
  int n_local;
  int *arr_local;
  
                    /* Unresolved local var: int[212][221] dp@[???] */
  uVar3 = (ulong)(n + 1);
  lVar1 = -0x58 - ((k + 1) * uVar3 * 4 + 0xf & 0xfffffffffffffff0);
  for (i = 0; i <= k; i = i + 1) {
    for (j = 0; j <= n; j = j + 1) {
      *(undefined4 *)((long)aiStack_58 + (long)j * 4 + (long)i * uVar3 * 4 + lVar1 + 0x58) = 0;
    }
  }
  for (i_1 = 1; i_1 <= k; i_1 = i_1 + 1) {
    for (j_1 = 1; j_1 <= n; j_1 = j_1 + 1) {
      *(undefined4 *)((long)aiStack_58 + (long)j_1 * 4 + (long)i_1 * uVar3 * 4 + lVar1 + 0x58) =
           *(undefined4 *)
            ((long)aiStack_58 + (long)(j_1 + -1) * 4 + (long)i_1 * uVar3 * 4 + lVar1 + 0x58);
      if ((arr[j_1 + -1] <= i_1) && (0 < arr[j_1 + -1])) {
        lVar2 = (long)i_1 * uVar3 * 4 + lVar1;
        *(int *)((long)aiStack_58 + (long)j_1 * 4 + lVar2 + 0x58) =
             *(int *)((long)aiStack_58 +
                     (long)(j_1 + -1) * 4 + (long)(i_1 / arr[j_1 + -1]) * uVar3 * 4 + lVar1 + 0x58)
             + 1 + *(int *)((long)aiStack_58 + (long)j_1 * 4 + lVar2 + 0x58);
      }
    }
  }
  return *(int *)((long)aiStack_58 + (long)n * 4 + (long)k * uVar3 * 4 + lVar1 + 0x58);
}