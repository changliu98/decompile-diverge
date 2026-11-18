char * func0(int *seq_nums,int n)

{
  int *piVar1;
  int local_48 [4];
  int i;
  int x;
  unsigned_long __vla_expr0;
  int n_local;
  int *seq_nums_local;
  
                    /* Unresolved local var: int[201] diff@[???] */
  piVar1 = (int *)((long)local_48 - ((ulong)(n - 1) * 4 + 0xf & 0xfffffffffffffff0));
  for (x = 1; x < n; x = x + 1) {
    piVar1[x + -1] = seq_nums[x] - seq_nums[x + -1];
  }
  i = 1;
  while( true ) {
    if (n + -1 <= i) {
      return "Linear Sequence";
    }
    if (piVar1[i] != *piVar1) break;
    i = i + 1;
  }
  return "Non Linear Sequence";
}