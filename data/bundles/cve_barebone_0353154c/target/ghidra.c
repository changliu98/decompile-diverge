void bit_write_UMC(Bit_Chain *dat,BITCODE_UMC val)

{
  BITCODE_UMC value;
  BITCODE_UMC mask;
  uchar byte [5];
  int negative;
  int j;
  int i;
  BITCODE_UMC val_local;
  Bit_Chain *dat_local;
  
  mask = 0x7f;
  j = 0;
  for (i = 4; -1 < i; i = i + -1) {
    byte[i] = (uchar)((val & mask) >> ((byte)j & 0x3f));
    byte[i] = byte[i] | 0x80;
    mask = mask << 7;
    j = j + 7;
  }
  i = 0;
  while ((i < 4 && ((byte[i] & 0x7f) == 0))) {
    i = i + 1;
  }
  if ((byte[i] & 0x40) != 0) {
    i = i + -1;
  }
  byte[i] = byte[i] & 0x7f;
  for (j = 4; i <= j; j = j + -1) {
    bit_write_RC(dat,byte[j]);
  }
  return;
}