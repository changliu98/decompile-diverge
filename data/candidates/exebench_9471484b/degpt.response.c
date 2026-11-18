void SdnToGregorian(long sdn,int *pYear,int *pMonth,int *pDay)

{
  int iVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  int dayOfYear;
  long temp;
  int day;
  int month;
  int year;
  int century;
  int *pDay_local;
  int *pMonth_local;
  int *pYear_local;
  long sdn_local;
  
  if ((sdn < 1) || (0x1fffffffffff82d2 < sdn)) {
    *pYear = 0;
    *pMonth = 0;
    *pDay = 0;
  }
  else {
    lVar3 = (sdn + 0x7d2d) * 4 + -1;
    lVar4 = ((lVar3 % 0x23ab1) / 4) * 4 + 3;
    year = (int)(lVar3 / 0x23ab1) * 100 + (int)(lVar4 / 0x5b5);
    iVar1 = ((int)((lVar4 % 0x5b5) / 4) + 1) * 5 + -3;
    iVar2 = iVar1 / 0x99;
    if (iVar2 < 10) {
      month = iVar2 + 3;
    }
    else {
      year = year + 1;
      month = iVar2 + -9;
    }
    iVar2 = year + -0x12c0;
    if (year + -0x12c0 < 1) {
      iVar2 = year + -0x12c1;
    }
    year = iVar2;
    *pYear = year;
    *pMonth = month;
    *pDay = (int)(((long)iVar1 % 0x99) / 5) + 1;
  }
  return;
}