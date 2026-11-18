void sun_mjulianday2date(long daynum,int *year,int *month,int *day)

{
  ulong uVar1;
  int iVar2;
  int iVar3;
  int h;
  int g;
  int e;
  int f;
  int *day_local;
  int *month_local;
  int *year_local;
  long daynum_local;
  
  iVar2 = ((int)daynum + (int)(((((daynum + 0x249f01) * 4 + 0x42f65) / 0x23ab1) * 3) / 4) + 0x24a454
          ) * 4 + 3;
  uVar1 = (long)iVar2 % 0x5b5;
  iVar3 = (int)((long)((ulong)(uint)((int)uVar1 >> 0x1f) << 0x20 | uVar1 & 0xffffffff) / 4) * 5 + 2;
  uVar1 = (long)iVar3 % 0x99;
  *day = (int)((long)((ulong)(uint)((int)uVar1 >> 0x1f) << 0x20 | uVar1 & 0xffffffff) / 5) + 1;
  *month = (iVar3 / 0x99 + 2) % 0xc + 1;
  *year = iVar2 / 0x5b5 + -0x126c + (0xe - *month) / 0xc;
  return;
}