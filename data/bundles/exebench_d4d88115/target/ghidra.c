void gsdate(int day,int mon,int year,int *serial)

{
  int iVar1;
  int i;
  int *serial_local;
  int year_local;
  int mon_local;
  int day_local;
  
  year_local = year + 100;
  if (mon < 3) {
    mon_local = mon + 9;
    year_local = year + 99;
  }
  else {
    mon_local = mon + -3;
  }
  iVar1 = (year_local * 0x5b5) / 4 + (mon_local * 0x99 + 2) / 5 + day;
  i = iVar1 + -0x8e72;
  if (0x3b < i) {
    i = iVar1 + -0x8e73;
  }
  *serial = i;
  return;
}