void eastero(int year,int *month,int *day)

{
  int iVar1;
  int e;
  int d;
  int c;
  int b;
  int a;
  int *day_local;
  int *month_local;
  int year_local;
  
  iVar1 = ((year % 0x13) * 0x13 + 0xf) % 0x1e;
  d = 10;
  if (0x640 < year) {
    d = (year / 100 - (year / 100 + -0x10) / 4) + -6;
  }
  iVar1 = (iVar1 - (year + year / 4 + iVar1) % 7) + d;
  *month = (iVar1 + 0x1a) / 0x1e + 3;
  *day = (iVar1 + 0x1b + (iVar1 + 6) / 0x28) % 0x1f + 1;
  return;
}