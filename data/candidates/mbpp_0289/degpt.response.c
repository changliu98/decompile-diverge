int func0(int N)

{
  int iVar1;
  int iVar2;
  int odd;
  int days;
  int ordd;
  int leap;
  int hund4;
  int hund1;
  int N_local;
  
  iVar1 = N / 100;
  iVar2 = N / 400;
  leap = N >> 2;
  ordd = N - leap;
  if (iVar1 != 0) {
    ordd = iVar1 + ordd;
    leap = leap - iVar1;
  }
  if (iVar2 != 0) {
    ordd = ordd - iVar2;
    leap = iVar2 + leap;
  }
  return (ordd + leap * 2) % 7;
}