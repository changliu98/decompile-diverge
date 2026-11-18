int ctsxs(uint x,int scale,uint *vscrp)

{
  uint uVar1;
  int iVar2;
  int local_2c;
  int mant;
  int exp;
  uint *vscrp_local;
  int scale_local;
  uint x_local;
  int local_c;
  
  uVar1 = x >> 0x17 & 0xff;
  if ((uVar1 == 0xff) && ((x & 0x7fffff) != 0)) {
    local_c = 0;
  }
  else {
    iVar2 = (uVar1 - 0x7f) + scale;
    if (iVar2 < 0) {
      local_c = 0;
    }
    else if (iVar2 < 0x1f) {
      local_2c = (int)((x & 0x7fffff | 0x800000) << 7) >> (0x1eU - (char)iVar2 & 0x1f);
      if ((x & 0x80000000) != 0) {
        local_2c = -local_2c;
      }
      local_c = local_2c;
    }
    else {
      if (x + scale * 0x800000 != -0x31000000) {
        *vscrp = VSCR_SAT | *vscrp;
      }
      local_c = 0x7fffffff;
      if ((x & 0x80000000) != 0) {
        local_c = -0x80000000;
      }
    }
  }
  return local_c;
}