int func0(int n)

{
  long lVar1;
  int iVar2;
  undefined4 auStack_48 [6];
  undefined4 *local_30;
  int temp;
  int i;
  unsigned_long __vla_expr0;
  int n_local;
  
                    /* Unresolved local var: int[177] res@[???] */
  lVar1 = -((ulong)(n + 1) * 4 + 0xf & 0xfffffffffffffff0);
  local_30 = (undefined4 *)((long)auStack_48 + lVar1);
  n_local = n;
  *local_30 = 0;
  *(undefined4 *)((long)auStack_48 + lVar1 + 4) = 1;
  for (i = 2; i < n_local + 1; i = i + 1) {
    local_30[i] = i;
    iVar2 = local_30[i / 2] + local_30[i / 3] + local_30[i / 4] + local_30[i / 5];
    if ((int)local_30[i] < iVar2) {
      local_30[i] = iVar2;
    }
  }
  return local_30[n_local];
}