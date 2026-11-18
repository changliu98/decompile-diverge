int i2s_sf_sclkdiv(int div,int *out)

{
  int d;
  int *out_local;
  int div_local;
  undefined4 local_c;
  
  if (div == 1) {
    *out = *out | 0x800000;
    local_c = 0;
  }
  else if (div == 3) {
    *out = *out | 0x900000;
    local_c = 0;
  }
  else if (div % 2 == 0) {
    if ((div / 2 == 9) || (div / 2 == 10)) {
      local_c = -1;
    }
    else {
      *out = (div / 2 - 1U & 0xf) << 0x14 | *out;
      local_c = 0;
    }
  }
  else {
    local_c = -1;
  }
  return local_c;
}