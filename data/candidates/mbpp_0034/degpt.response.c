int func0(int *ar,int N)

{
  int iVar1;
  int mid;
  int r;
  int l;
  int N_local;
  int *ar_local;
  
  l = 0;
  r = N + -1;
  while( true ) {
    if (r < l) {
      return -1;
    }
    iVar1 = (l + r) / 2;
    if ((ar[iVar1] != iVar1 + 1) && (ar[iVar1 + -1] == iVar1)) break;
    if (ar[iVar1] == iVar1 + 1) {
      l = iVar1 + 1;
    }
    else {
      r = iVar1 + -1;
    }
  }
  return iVar1 + 1;
}