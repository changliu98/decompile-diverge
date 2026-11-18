void SdnToJulian(long sdn,int *pYear,int *pMonth,int *pDay)

{
  int iVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  long yearl;
  int dayOfYear;
  long temp;
  int day;
  int month;
  int year;
  int *pDay_local;
  int *pMonth_local;
  int *pYear_local;
  long sdn_local;
  
  if (((0 < sdn) && (sdn < 0x1fffffffffff82ae)) && (-0x2000000000000001 < sdn)) {
    lVar3 = sdn * 4 + 0x1f54b;
    lVar4 = lVar3 / 0x5b5;
    if ((lVar4 < 0x80000000) && (-0x80000001 < lVar4)) {
      year = (int)lVar4;
      iVar1 = ((int)((lVar3 % 0x5b5) / 4) + 1) * 5 + -3;
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
      return;
    }
  }
  *pYear = 0;
  *pMonth = 0;
  *pDay = 0;
  return;
}