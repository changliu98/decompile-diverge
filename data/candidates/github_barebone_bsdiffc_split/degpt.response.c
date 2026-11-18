void split(int64_t *I,int64_t *V,int64_t start,int64_t len,int64_t h)

{
  int64_t iVar1;
  long lVar2;
  long lVar3;
  long start_00;
  int64_t kk;
  int64_t jj;
  int64_t tmp;
  int64_t x;
  int64_t k;
  int64_t j;
  int64_t i;
  int64_t h_local;
  int64_t len_local;
  int64_t start_local;
  int64_t *V_local;
  int64_t *I_local;
  
  k = start;
  if (len < 0x10) {
    for (; k < start + len; k = j + k) {
      j = 1;
      x = V[I[k] + h];
      for (i = 1; k + i < start + len; i = i + 1) {
        if (V[I[k + i] + h] < x) {
          x = V[I[k + i] + h];
          j = 0;
        }
        if (V[I[k + i] + h] == x) {
          iVar1 = I[k + j];
          I[k + j] = I[k + i];
          I[k + i] = iVar1;
          j = j + 1;
        }
      }
      for (i = 0; i < j; i = i + 1) {
        V[I[k + i]] = k + j + -1;
      }
      if (j == 1) {
        I[k] = -1;
      }
    }
  }
  else {
    lVar2 = V[I[start + len / 2] + h];
    jj = 0;
    kk = 0;
    for (i = start; i < start + len; i = i + 1) {
      if (V[I[i] + h] < lVar2) {
        jj = jj + 1;
      }
      if (V[I[i] + h] == lVar2) {
        kk = kk + 1;
      }
    }
    lVar3 = start + jj;
    start_00 = lVar3 + kk;
    j = 0;
    k = 0;
    i = start;
    while (i < lVar3) {
      if (V[I[i] + h] < lVar2) {
        i = i + 1;
      }
      else if (V[I[i] + h] == lVar2) {
        iVar1 = I[i];
        I[i] = I[lVar3 + j];
        I[lVar3 + j] = iVar1;
        j = j + 1;
      }
      else {
        iVar1 = I[i];
        I[i] = I[start_00 + k];
        I[start_00 + k] = iVar1;
        k = k + 1;
      }
    }
    while (lVar3 + j < start_00) {
      if (V[I[lVar3 + j] + h] == lVar2) {
        j = j + 1;
      }
      else {
        iVar1 = I[lVar3 + j];
        I[lVar3 + j] = I[start_00 + k];
        I[start_00 + k] = iVar1;
        k = k + 1;
      }
    }
    if (start < lVar3) {
      split(I,V,start,lVar3 - start,h);
    }
    for (i = 0; i < start_00 - lVar3; i = i + 1) {
      V[I[lVar3 + i]] = start_00 + -1;
    }
    if (lVar3 == start_00 + -1) {
      I[lVar3] = -1;
    }
    if (start_00 < start + len) {
      split(I,V,start_00,(start + len) - start_00,h);
    }
  }
  return;
}