int next(int *mask,int n)

{
  bool bVar1;
  int i;
  int n_local;
  int *mask_local;
  uint local_c;
  
  i = 0;
  while( true ) {
    bVar1 = false;
    if (i < n) {
      bVar1 = mask[i] != 0;
    }
    if (!bVar1) break;
    mask[i] = 0;
    i = i + 1;
  }
  if (i < n) {
    mask[i] = 1;
  }
  local_c = (uint)(i < n);
  return local_c;
}