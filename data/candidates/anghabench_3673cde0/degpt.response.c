float modff(float x,float *iptr)

{
  int iVar1;
  uint uVar2;
  int e;
  uint32_t mask;
  anon_union_4_2_947300a4 u;
  float *iptr_local;
  float x_local;
  undefined4 local_c;
  
  iVar1 = ((uint)x >> 0x17 & 0xff) - 0x7f;
  local_c = x;
  if (iVar1 < 0x17) {
    if (iVar1 < 0) {
      *iptr = (float)((uint)x & 0x80000000);
    }
    else {
      uVar2 = 0x7fffff >> ((byte)iVar1 & 0x1f);
      if (((uint)x & uVar2) == 0) {
        *iptr = x;
        local_c = (float)((uint)x & 0x80000000);
      }
      else {
        local_c = (float)((uVar2 ^ 0xffffffff) & (uint)x);
        *iptr = local_c;
        local_c = x - local_c;
      }
    }
  }
  else {
    *iptr = x;
    if ((iVar1 != 0x80) || (((uint)x & 0x7fffff) == 0)) {
      local_c = (float)((uint)x & 0x80000000);
    }
  }
  return local_c;
}