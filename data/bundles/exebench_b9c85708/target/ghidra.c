void easterj(int year,int *month,int *day)

{
  int iVar1;
  int iVar2;
  int g;
  int f;
  int e;
  int d;
  int c;
  int b;
  int a;
  int *day_local;
  int *month_local;
  int year_local;
  
  iVar1 = ((year % 0x13) * 0x13 + 0xf) % 0x1e;
  iVar2 = ((((year % 4) * 2 + (year % 7) * 4) - iVar1) + 0x22) % 7;
  *month = (iVar1 + iVar2 + 0x72) / 0x1f;
  *day = (iVar1 + iVar2 + 0x72) % 0x1f + 1;
  return;
}