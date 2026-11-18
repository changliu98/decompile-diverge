void func0(int *A,int *B,int *C,int p,int q,int r,int *res)

{
  bool bVar1;
  int local_6c;
  int local_68;
  int local_64;
  int local_60;
  int local_5c;
  int local_58;
  int maximum;
  int minimum;
  int k;
  int j;
  int i;
  int res_k;
  int res_j;
  int res_i;
  int diff;
  int r_local;
  int q_local;
  int p_local;
  int *C_local;
  int *B_local;
  int *A_local;
  
  diff = 0x7fffffff;
  res_i = 0;
  res_j = 0;
  res_k = 0;
  i = 0;
  j = 0;
  k = 0;
  while( true ) {
    bVar1 = false;
    if ((i < p) && (bVar1 = false, j < q)) {
      bVar1 = k < r;
    }
    if (!bVar1) break;
    if (A[i] < B[j]) {
      if (A[i] < C[k]) {
        local_58 = A[i];
      }
      else {
        local_58 = C[k];
      }
      local_5c = local_58;
    }
    else {
      if (B[j] < C[k]) {
        local_60 = B[j];
      }
      else {
        local_60 = C[k];
      }
      local_5c = local_60;
    }
    if (B[j] < A[i]) {
      if (C[k] < A[i]) {
        local_64 = A[i];
      }
      else {
        local_64 = C[k];
      }
      local_68 = local_64;
    }
    else {
      if (C[k] < B[j]) {
        local_6c = B[j];
      }
      else {
        local_6c = C[k];
      }
      local_68 = local_6c;
    }
    if (local_68 - local_5c < diff) {
      res_i = i;
      res_j = j;
      res_k = k;
      diff = local_68 - local_5c;
    }
    if (diff == 0) break;
    if (A[i] == local_5c) {
      i = i + 1;
    }
    else if (B[j] == local_5c) {
      j = j + 1;
    }
    else {
      k = k + 1;
    }
  }
  *res = A[res_i];
  res[1] = B[res_j];
  res[2] = C[res_k];
  return;
}