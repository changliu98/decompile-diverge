int gen256(uchar *dst,uint prim_poly)

{
  uint v;
  int i;
  uint identity;
  uint prim_poly_local;
  uchar *dst_local;
  int local_c;
  
  if ((prim_poly & 0x100) == 0) {
    local_c = -1;
  }
  else {
    *dst = '\0';
    dst[1] = '\x01';
    v = 1;
    for (i = 2; i < 0x100; i = i + 1) {
      v = v << 1;
      if ((v & 0x100) != 0) {
        v = prim_poly & 0xff ^ v & 0xff;
      }
      dst[i] = (uchar)v;
    }
    local_c = 0;
  }
  return local_c;
}