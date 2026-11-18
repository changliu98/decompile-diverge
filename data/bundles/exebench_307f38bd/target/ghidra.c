/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void multiply(int factor1,int factor2,int *prod)

{
  uint uVar1;
  double dVar2;
  double dAccum;
  int low;
  uint tmp;
  int *prod_local;
  int factor2_local;
  int factor1_local;
  
  uVar1 = factor1 * factor2 & 0x7fffffff;
  *prod = uVar1;
  if (uVar1 < 0x40000000) {
    dVar2 = _DAT_00102010 + (double)factor1 * (double)factor2;
  }
  else {
    dVar2 = (double)factor1 * (double)factor2 - _DAT_00102010;
  }
  dAccum = dVar2 / DAT_00102008;
  prod[1] = (int)(long)dAccum;
  return;
}