/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int func0(int n)

{
  double dVar1;
  double dVar2;
  double x;
  int n_local;
  undefined4 local_c;
  
  if (n < 0) {
    local_c = 0;
  }
  else if (n < 2) {
    local_c = 1;
  }
  else {
    dVar1 = log10((double)n / _DAT_00102018);
    dVar2 = log10(DAT_00102010 * (double)n);
    dVar1 = floor((double)n * dVar1 + dVar2 / DAT_00102008);
    local_c = (int)dVar1 + 1;
  }
  return local_c;
}