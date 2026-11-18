int unicoder_utf32_decode(uint *result,uchar *p,uint endianness)

{
  uint decoded;
  int i;
  uint endianness_local;
  uchar *p_local;
  uint *result_local;
  int local_c;
  
  if ((endianness == 2) || (endianness == 1)) {
    if (p == (uchar *)0x0) {
      local_c = -1;
    }
    else if (result == (uint *)0x0) {
      local_c = -1;
    }
    else {
      decoded = 0;
      for (i = 0; i < 4; i = i + 1) {
        if (endianness == 2) {
          if (0 < i) {
            decoded = decoded << 8;
          }
          decoded = p[i] | decoded;
        }
        else {
          if (0 < i) {
            decoded = decoded >> 8;
          }
          decoded = (uint)p[i] << 0x18 | decoded;
        }
      }
      if (decoded < 0x110000) {
        if ((decoded < 0xd800) || (0xdfff < decoded)) {
          *result = decoded;
          local_c = 4;
        }
        else {
          local_c = -0x10;
        }
      }
      else {
        local_c = -0x10;
      }
    }
  }
  else {
    local_c = -4;
  }
  return local_c;
}