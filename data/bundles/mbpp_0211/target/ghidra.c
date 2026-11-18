/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int func0(int n)

{
  double dVar1;
  int count;
  int n_local;
  undefined4 local_c;
  
  if (n == 1) {
    local_c = 1;
  }
  else {
    dVar1 = pow(_DAT_00102008,(double)(n + -2));
    local_c = (int)dVar1;
  }
  return local_c;
}