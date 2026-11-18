int func0(int n,int r,int p)

{
  undefined4 *puVar1;
  int aiStack_48 [2];
  undefined4 *local_40;
  int j;
  int i_1;
  int i;
  unsigned_long __vla_expr0;
  int p_local;
  int r_local;
  int n_local;
  
                    /* Unresolved local var: int[199] C@[???] */
  puVar1 = (undefined4 *)((long)aiStack_48 - ((ulong)(r + 1) * 4 + 0xf & 0xfffffffffffffff0));
  for (i = 0; i <= r; i = i + 1) {
    puVar1[i] = 0;
  }
  local_40 = puVar1;
  p_local = p;
  r_local = r;
  n_local = n;
  *puVar1 = 1;
  for (i_1 = 1; i_1 <= n_local; i_1 = i_1 + 1) {
    if (i_1 < r_local) {
      aiStack_48[1] = i_1;
    }
    else {
      aiStack_48[1] = r_local;
    }
    for (j = aiStack_48[1]; 0 < j; j = j + -1) {
      local_40[j] = (int)(local_40[j] + local_40[j + -1]) % p_local;
    }
  }
  return local_40[r_local];
}