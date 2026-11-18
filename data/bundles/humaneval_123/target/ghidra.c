void func0(int n,int *out,int *size)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  int j;
  int key;
  int i;
  int capacity;
  int *size_local;
  int *out_local;
  int n_local;
  
  capacity = 10;
  *size = 1;
  *out = 1;
  out_local = out;
  n_local = n;
  while (n_local != 1) {
    if (n_local % 2 == 1) {
      if (capacity <= *size) {
        capacity = capacity << 1;
        out_local = realloc(out_local,(long)capacity << 2);
      }
      iVar1 = *size;
      *size = iVar1 + 1;
      out_local[iVar1] = n_local;
      n_local = n_local * 3 + 1;
    }
    else {
      n_local = n_local / 2;
    }
  }
  for (i = 1; i < *size; i = i + 1) {
    iVar1 = out_local[i];
    iVar3 = i;
    while( true ) {
      j = iVar3 + -1;
      bVar2 = false;
      if (-1 < j) {
        bVar2 = iVar1 < out_local[j];
      }
      if (!bVar2) break;
      out_local[iVar3] = out_local[j];
      iVar3 = j;
    }
    out_local[iVar3] = iVar1;
  }
  return;
}