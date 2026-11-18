void easterg(int year,int *month,int *day)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int p;
  int n;
  int m;
  int l;
  int k;
  int i;
  int h;
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
  
  iVar1 = year / 100;
  iVar2 = (((((year % 0x13) * 0x13 + iVar1) - iVar1 / 4) - ((iVar1 - (iVar1 + 8) / 0x19) + 1) / 3) +
          0xf) % 0x1e;
  iVar3 = ((((iVar1 % 4) * 2 + 0x20 + ((year % 100) / 4) * 2) - iVar2) - (year % 100) % 4) % 7;
  iVar1 = (year % 0x13 + iVar2 * 0xb + iVar3 * 0x16) / 0x1c3;
  *month = (iVar2 + iVar3 + iVar1 * -7 + 0x72) / 0x1f;
  *day = (iVar2 + iVar3 + iVar1 * -7 + 0x72) % 0x1f + 1;
  return;
}