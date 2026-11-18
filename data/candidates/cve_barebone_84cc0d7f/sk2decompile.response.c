void faad_resetbits(bitfile *ld, int nbits) {
  int nwords = nbits >> 5;
  ld->bits_left = ld->buffer_size - (nwords << 2);
  if (ld->bits_left >= 4) {
    ld->bufa = getdword(ld->start + nwords);
    ld->bits_left -= 4;
  } else {
    ld->bufa = getdword_n(ld->start + nwords, ld->bits_left);
    ld->bits_left = 0;
  }
  if (ld->bits_left >= 4) {
    ld->bufb = getdword(ld->start + nwords + 1);
    ld->bits_left -= 4;
  } else {
    ld->bufb = getdword_n(ld->start + nwords + 1, ld->bits_left);
    ld->bits_left = 0;
  }
  ld->run_len = 32 - (nbits & 31);
  ld->tail = ld->start + nwords + 2;
  ld->error = 0;
}