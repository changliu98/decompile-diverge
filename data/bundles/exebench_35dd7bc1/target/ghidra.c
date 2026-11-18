int i2s_sf_mclkdiv(int div,int *out)

{
  int iVar1;
  int d;
  int *out_local;
  int div_local;
  int local_c;
  
  switch(div) {
  case 1:
    *out = *out | 0x14000000;
    local_c = 0;
    break;
  default:
    if (div % 2 == 0) {
      iVar1 = div / 2;
      if ((((iVar1 == 0x15) || (iVar1 == 0x14)) || (iVar1 == 0x13)) || (iVar1 == 0xf)) {
        local_c = -1;
      }
      else {
        *out = (div / 2 - 1U & 0x1f) << 0x18 | *out;
        local_c = 0;
      }
    }
    else {
      local_c = -1;
    }
    break;
  case 3:
    *out = *out | 0x13000000;
    local_c = 0;
    break;
  case 5:
    *out = *out | 0x12000000;
    local_c = 0;
    break;
  case 0xe:
    *out = *out | 0xe000000;
    local_c = 0;
  }
  return local_c;
}