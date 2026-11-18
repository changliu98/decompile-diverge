void faad_resetbits(bitfile *ld,int bits)

{
  int iVar1;
  int remainder;
  int words;
  uint32_t tmp;
  int bits_local;
  bitfile *ld_local;
  
  iVar1 = bits >> 5;
  ld->bytes_left = ld->buffer_size + iVar1 * -4;
  if (ld->bytes_left < 4) {
    tmp = getdword_n(ld->start + iVar1,ld->bytes_left);
    ld->bytes_left = 0;
  }
  else {
    tmp = getdword(ld->start + iVar1);
    ld->bytes_left = ld->bytes_left - 4;
  }
  ld->bufa = tmp;
  if (ld->bytes_left < 4) {
    tmp = getdword_n(ld->start + (iVar1 + 1),ld->bytes_left);
    ld->bytes_left = 0;
  }
  else {
    tmp = getdword(ld->start + (iVar1 + 1));
    ld->bytes_left = ld->bytes_left - 4;
  }
  ld->bufb = tmp;
  ld->bits_left = 0x20 - (bits & 0x1fU);
  ld->tail = ld->start + (iVar1 + 2);
  ld->error = '\0';
  return;
}