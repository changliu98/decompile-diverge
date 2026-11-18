/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int func0(int n)

{
  double dVar1;
  int pos;
  int n_local;
  undefined4 local_c;
  
  if (n == 0) {
    local_c = 1;
  }
  else {
    local_c = n;
    if ((n & n + 1U) != 0) {
      dVar1 = log2((double)(int)((n ^ 0xffffffffU) & -(n ^ 0xffffffffU)));
      local_c = 1 << ((char)(int)(dVar1 + _DAT_00102008) - 1U & 0x1f) | n;
    }
  }
  return local_c;
}