void swap(int *p)

{
  int iVar1;
  int *pmin;
  int *pmax;
  int temp;
  int j;
  int i;
  int *p_local;
  
  pmin = p;
  pmax = p;
  for (i = 0; i < 5; i = i + 1) {
    for (j = i; j < 5; j = j + 1) {
      if (*pmax < p[(long)(i * 5) + (long)j]) {
        pmax = p + (long)(i * 5) + (long)j;
      }
      if (p[(long)(i * 5) + (long)j] < *pmin) {
        pmin = p + (long)(i * 5) + (long)j;
      }
    }
  }
  iVar1 = p[0xc];
  p[0xc] = *pmax;
  *pmax = iVar1;
  *pmin = *pmin;
  pmin = p + 1;
  for (i = 0; i < 5; i = i + 1) {
    for (j = 0; j < 5; j = j + 1) {
      if (((i != 0) || (j != 0)) && (p[(long)(i * 5) + (long)j] < *pmin)) {
        pmin = p + (long)(i * 5) + (long)j;
      }
    }
  }
  iVar1 = *pmin;
  *pmin = p[4];
  p[4] = iVar1;
  pmin = p + 1;
  for (i = 0; i < 5; i = i + 1) {
    for (j = 0; j < 5; j = j + 1) {
      if ((((i != 0) || (j != 0)) && ((i != 0 || (j != 4)))) && (p[(long)(i * 5) + (long)j] < *pmin)
         ) {
        pmin = p + (long)(i * 5) + (long)j;
      }
    }
  }
  iVar1 = *pmin;
  *pmin = p[0x14];
  p[0x14] = iVar1;
  pmin = p + 1;
  for (i = 0; i < 5; i = i + 1) {
    for (j = 0; j < 5; j = j + 1) {
      if (((i != 0) || (j != 0)) &&
         (((i != 0 || (j != 4)) && (((i != 4 || (j != 0)) && (p[(long)(i * 5) + (long)j] < *pmin))))
         )) {
        pmin = p + (long)(i * 5) + (long)j;
      }
    }
  }
  iVar1 = *pmin;
  *pmin = p[0x18];
  p[0x18] = iVar1;
  return;
}