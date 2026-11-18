void julian_to_date(long jd,int *y,int *m,int *d)

{
  int iVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  long j;
  long i;
  long n;
  long L;
  int *d_local;
  int *m_local;
  int *y_local;
  long jd_local;
  
  lVar2 = ((jd + 0x10bd9) * 4) / 0x23ab1;
  lVar3 = (jd + 0x10bd9) - (lVar2 * 0x23ab1 + 3) / 4;
  lVar4 = ((lVar3 + 1) * 4000) / 0x164b09;
  lVar3 = (lVar3 - (lVar4 * 0x5b5) / 4) + 0x1f;
  lVar5 = (lVar3 * 0x50) / 0x98f;
  *d = (int)lVar3 - (int)((lVar5 * 0x98f) / 0x50);
  iVar1 = (int)(lVar5 / 0xb);
  *m = (int)lVar5 + 2 + iVar1 * -0xc;
  *y = ((int)lVar2 + -0x31) * 100 + (int)lVar4 + iVar1;
  return;
}