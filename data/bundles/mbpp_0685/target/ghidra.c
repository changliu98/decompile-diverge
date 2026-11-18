int func0(int n)

{
  long lVar1;
  byte abStack_48 [20];
  int i_1;
  int sum;
  int i;
  int p;
  int j;
  unsigned_long __vla_expr0;
  int n_local;
  
                    /* Unresolved local var: _Bool[177] prime@[???] */
  lVar1 = -0x48 - ((ulong)(n + 1) + 0xf & 0xfffffffffffffff0);
  for (j = 0; j <= n; j = j + 1) {
    abStack_48[j + lVar1 + 0x48] = 1;
  }
  for (p = 2; p * p <= n; p = p + 1) {
    if ((abStack_48[p + lVar1 + 0x48] & 1) == 1) {
      for (i = p << 1; i <= n; i = p + i) {
        abStack_48[i + lVar1 + 0x48] = 0;
      }
    }
  }
  sum = 0;
  for (i_1 = 2; i_1 <= n; i_1 = i_1 + 1) {
    if ((abStack_48[i_1 + lVar1 + 0x48] & 1) != 0) {
      sum = i_1 + sum;
    }
  }
  return sum;
}