uint8_t gfmul(uint8_t a,uint8_t b)

{
  byte bVar1;
  uint8_t v;
  uint8_t b_local;
  uint8_t a_local;
  
  v = '\0';
  a_local = a;
  for (b_local = b; b_local != '\0'; b_local = (uint8_t)((int)(uint)b_local >> 1)) {
    if ((b_local & 1) != 0) {
      v = v ^ a_local;
    }
    bVar1 = 0;
    if ((a_local & 0x80) != 0) {
      bVar1 = 0x1d;
    }
    a_local = a_local << 1 ^ bVar1;
  }
  return v;
}