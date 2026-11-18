uint mul_poly(uint a,uint b,uint poly)

{
  uint c;
  uint poly_local;
  uint b_local;
  uint a_local;
  
  c = 0;
  b_local = b;
  a_local = a;
  while (a_local != 0) {
    if ((a_local & 1) != 0) {
      c = b_local ^ c;
    }
    a_local = a_local >> 1;
    b_local = b_local << 1;
    if ((b_local & 0x10000) != 0) {
      b_local = poly ^ b_local;
    }
  }
  return c;
}