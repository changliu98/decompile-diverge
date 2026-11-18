int denormal_addf1(uint ix,uint iy)

{
  uint uVar1;
  int exp;
  int frac;
  uint iy_local;
  uint ix_local;
  uint local_c;
  
  if (ix < 0x800000) {
    local_c = ix + iy;
  }
  else {
    exp = (ix & 0x7f800000) >> 0x17;
    local_c = ix;
    if (((int)(exp - 1U) < 0x20) && (uVar1 = iy >> ((char)exp - 1U & 0x1f), uVar1 != 0)) {
      frac = uVar1 + (ix & 0x7fffff | 0x800000);
      if (0xffffff < frac) {
        frac = frac >> 1;
        exp = exp + 1;
      }
      local_c = exp << 0x17 | frac & 0x7fffffU;
    }
  }
  return local_c;
}