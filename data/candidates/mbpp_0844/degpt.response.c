int func0(int n,int k)

{
  long lVar1;
  int local_38 [3];
  int even;
  int odd;
  int i;
  unsigned_long __vla_expr0;
  int k_local;
  int n_local;
  
                    /* Unresolved local var: int[188] arr@[???] */
  lVar1 = -0x38 - ((ulong)(uint)n * 4 + 0xf & 0xfffffffffffffff0);
  i = 0;
  for (odd = 1; odd <= n; odd = odd + 2) {
    *(int *)((long)local_38 + (long)i * 4 + lVar1 + 0x38) = odd;
    i = i + 1;
  }
  for (even = 2; even <= n; even = even + 2) {
    *(int *)((long)local_38 + (long)i * 4 + lVar1 + 0x38) = even;
    i = i + 1;
  }
  return *(int *)((long)local_38 + (long)(k + -1) * 4 + lVar1 + 0x38);
}