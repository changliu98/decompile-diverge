int func0(int n)

{
  long lVar1;
  undefined4 local_38 [2];
  undefined4 *local_30;
  int i;
  unsigned_long __vla_expr0;
  int n_local;
  
                    /* Unresolved local var: int[177] dp@[???] */
  lVar1 = -((ulong)(n + 1) * 4 + 0xf & 0xfffffffffffffff0);
  local_30 = (undefined4 *)((long)local_38 + lVar1);
  n_local = n;
  *local_30 = 0;
  *(undefined4 *)((long)local_38 + lVar1 + 4) = 1;
  for (i = 2; i <= n_local; i = i + 1) {
    local_30[i] = local_30[i / 2] + local_30[i / 3] + local_30[i / 4];
    if ((int)local_30[i] < i) {
      local_30[i] = i;
    }
  }
  return local_30[n_local];
}