int func0(int n,int a,int b,int c)

{
  undefined4 *puVar1;
  int aiStack_48 [4];
  undefined4 *local_38;
  int i_1;
  int i;
  unsigned_long __vla_expr0;
  int c_local;
  int b_local;
  int a_local;
  int n_local;
  
                    /* Unresolved local var: int[210] dp@[???] */
  puVar1 = (undefined4 *)((long)aiStack_48 - ((ulong)(n + 10) * 4 + 0xf & 0xfffffffffffffff0));
  for (i = 0; i < n + 10; i = i + 1) {
    puVar1[i] = 0xffffffff;
  }
  local_38 = puVar1;
  c_local = c;
  b_local = b;
  a_local = a;
  n_local = n;
  *puVar1 = 0;
  for (i_1 = 0; i_1 <= n_local; i_1 = i_1 + 1) {
    if (local_38[i_1] != -1) {
      if (i_1 + a_local <= n_local) {
        if ((int)local_38[i_1 + a_local] < local_38[i_1] + 1) {
          aiStack_48[3] = local_38[i_1] + 1;
        }
        else {
          aiStack_48[3] = local_38[i_1 + a_local];
        }
        local_38[i_1 + a_local] = aiStack_48[3];
      }
      if (i_1 + b_local <= n_local) {
        if ((int)local_38[i_1 + b_local] < local_38[i_1] + 1) {
          aiStack_48[2] = local_38[i_1] + 1;
        }
        else {
          aiStack_48[2] = local_38[i_1 + b_local];
        }
        local_38[i_1 + b_local] = aiStack_48[2];
      }
      if (i_1 + c_local <= n_local) {
        if ((int)local_38[i_1 + c_local] < local_38[i_1] + 1) {
          aiStack_48[1] = local_38[i_1] + 1;
        }
        else {
          aiStack_48[1] = local_38[i_1 + c_local];
        }
        local_38[i_1 + c_local] = aiStack_48[1];
      }
    }
  }
  return local_38[n_local];
}