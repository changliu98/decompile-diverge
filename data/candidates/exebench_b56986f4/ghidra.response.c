void makeipt(int nw,int *ip)

{
  int iVar1;
  int iVar2;
  int q;
  int p;
  int m2;
  int m;
  int l;
  int j;
  int *ip_local;
  int nw_local;
  
  ip[2] = 0;
  ip[3] = 0x10;
  m = 2;
  for (l = nw; 0x20 < l; l = l >> 2) {
    iVar2 = m * 2;
    for (j = m; j < iVar2; j = j + 1) {
      iVar1 = ip[j];
      ip[m + j] = iVar1 * 4;
      ip[iVar2 + j] = iVar1 * 4 + m * 0x10;
    }
    m = iVar2;
  }
  return;
}