void numpar(double *param,int *len,int *out)

{
  long lVar1;
  int local_58 [2];
  double diff;
  int count;
  unsigned_long __vla_expr0;
  int k;
  int j;
  int i;
  int *out_local;
  int *len_local;
  double *param_local;
  
                    /* Unresolved local var: int[246] jump@[???] */
  i = -1;
  lVar1 = -0x58 - ((ulong)(uint)*len * 4 + 0xf & 0xfffffffffffffff0);
  count = -1;
  while (i < *len + -1) {
    i = i + 1;
    for (j = 0; k = i, j < count; j = j + 1) {
      if (i == *(int *)((long)local_58 + (long)j * 4 + lVar1 + 0x58)) {
        i = i + 1;
      }
    }
    while (k = k + 1, k < *len) {
      for (j = 0; j < count; j = j + 1) {
        if (k == *(int *)((long)local_58 + (long)j * 4 + lVar1 + 0x58)) {
          k = k + 1;
        }
      }
      diff = param[i] - param[k];
      if (diff < 0.0) {
        diff = DAT_00102008 * diff;
      }
      if ((diff == 0.0) && (!NAN(diff))) {
        *(int *)((long)local_58 + (long)(count + 1) * 4 + lVar1 + 0x58) = k;
        *out = *out + -1;
        count = count + 1;
      }
    }
  }
  return;
}