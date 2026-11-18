void sun_mjulianday_to_date(uint mjd,int *year,int *month,int *day)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int m;
  int e;
  int d;
  int c;
  int b;
  int a;
  int *day_local;
  int *month_local;
  int *year_local;
  uint mjd_local;
  
  iVar1 = (int)((mjd + 0x251c2d) * 4 + 3) / 0x23ab1;
  iVar2 = (mjd + 0x251c2d) - (iVar1 * 0x23ab1) / 4;
  iVar3 = (iVar2 * 4 + 3) / 0x5b5;
  iVar2 = iVar2 - (iVar3 * 0x5b5) / 4;
  iVar4 = (iVar2 * 5 + 2) / 0x99;
  *day = (iVar2 - (iVar4 * 0x99 + 2) / 5) + 1;
  *month = iVar4 + 3 + (iVar4 / 10) * -0xc;
  *year = iVar1 * 100 + iVar3 + -0x12c0 + iVar4 / 10;
  return;
}