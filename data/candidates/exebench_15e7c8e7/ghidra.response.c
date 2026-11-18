void j2gcal(int *y,int *m,int *d,double j)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int x;
  int n;
  int l;
  int i;
  double j_local;
  int *d_local;
  int *m_local;
  int *y_local;
  
  iVar1 = (int)(DAT_00102008 + j) + 0x10bd9;
  iVar2 = (iVar1 * 4) / 0x23ab1;
  iVar1 = iVar1 - (iVar2 * 0x23ab1 + 3) / 4;
  iVar3 = ((iVar1 + 1) * 4000) / 0x164b09;
  iVar1 = iVar1 - ((iVar3 * 0x5b5) / 4 + -0x1f);
  iVar4 = (iVar1 * 0x50) / 0x98f;
  *d = iVar1 - (iVar4 * 0x98f) / 0x50;
  *m = iVar4 + 2 + (iVar4 / 0xb) * -0xc;
  *y = (iVar2 + -0x31) * 100 + iVar3 + iVar4 / 0xb;
  return;
}