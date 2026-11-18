int func0(int *a,int n)

{
  int *local_48;
  int i_1;
  int max_val;
  int j;
  int mxm;
  int i;
  unsigned_long __vla_expr0;
  int n_local;
  int *a_local;
  
                    /* Unresolved local var: int[201] dp@[???] */
  local_48 = (int *)((long)&local_48 - ((ulong)(uint)n * 4 + 0xf & 0xfffffffffffffff0));
  n_local = n;
  a_local = a;
  local_48[n + -1] = 1;
  for (i = n_local + -2; -1 < i; i = i + -1) {
    mxm = 0;
    j = i;
    while (j = j + 1, j < n_local) {
      if (((a_local[j] % a_local[i] == 0) || (a_local[i] % a_local[j] == 0)) && (mxm < local_48[j]))
      {
        mxm = local_48[j];
      }
    }
    local_48[i] = mxm + 1;
  }
  max_val = *local_48;
  for (i_1 = 1; i_1 < n_local; i_1 = i_1 + 1) {
    if (max_val < local_48[i_1]) {
      max_val = local_48[i_1];
    }
  }
  return max_val;
}