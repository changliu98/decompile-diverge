_Bool func0(int *arr,int n,int m)

{
  byte *pbVar1;
  ulong uVar2;
  byte abStack_78 [28];
  int j_1;
  int j;
  int k;
  unsigned_long __vla_expr1;
  int i_1;
  int i;
  unsigned_long __vla_expr0;
  int m_local;
  int n_local;
  int *arr_local;
  _Bool local_9;
  
                    /* Unresolved local var: _Bool[212] DP@[???] */
  if (m < n) {
    local_9 = true;
  }
  else {
    pbVar1 = abStack_78 + -((ulong)(uint)m + 0xf & 0xfffffffffffffff0);
    for (i = 0; i < m; i = i + 1) {
      pbVar1[i] = 0;
    }
    for (i_1 = 0; i_1 < n; i_1 = i_1 + 1) {
                    /* Unresolved local var: _Bool[271] temp@[???] */
      if ((*pbVar1 & 1) != 0) {
        return true;
      }
      uVar2 = (ulong)(uint)m + 0xf & 0xfffffffffffffff0;
      for (k = 0; k < m; k = k + 1) {
        pbVar1[(long)k - uVar2] = 0;
      }
      for (j = 0; j < m; j = j + 1) {
        if (((pbVar1[j] & 1) != 0) && ((pbVar1[(j + arr[i_1]) % m] & 1) == 0)) {
          pbVar1[(long)((j + arr[i_1]) % m) - uVar2] = 1;
        }
      }
      for (j_1 = 0; j_1 < m; j_1 = j_1 + 1) {
        if ((pbVar1[(long)j_1 - uVar2] & 1) != 0) {
          pbVar1[j_1] = 1;
        }
      }
      pbVar1[arr[i_1] % m] = 1;
    }
    local_9 = (_Bool)(*pbVar1 & 1);
  }
  return local_9;
}