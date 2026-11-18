void TH_float2halfbits(float *f, unsigned short *h) {
  unsigned int fbits = *(unsigned int *)f;
  unsigned int fexp = fbits & 0x7fffffff;
  if (fexp > 0x7f800000) {
    *h = 0x7fff;
    return;
  }
  unsigned int fsign = (fbits & 0x80000000) >> 16;
  if (fexp >= 0x47800001) {
    *h = fsign | 0x7c00;
    return;
  }
  if (fexp < 0x38000001) {
    *h = fsign;
    return;
  }
  unsigned int fman_exp = (fexp >> 23) & 0xff;
  unsigned int fman_mant = fexp & 0x007fffff;
  unsigned int shift;
  unsigned int fman_exp_out;
  unsigned int fman_mant_out;
  if (fman_exp >= 0x70) {
    shift = 13;
    fman_exp_out = fman_exp - 0x70;
  } else {
    shift = 0x7e - fman_exp;
    fman_exp_out = 0;
    fman_mant |= 0x00800000;
  }
  unsigned int halfway = (1 << shift) >> 1;
  fman_mant_out = fman_mant & ((1 << shift) - 1);
  fman_mant = fman_mant >> shift;
  if (fman_mant_out > halfway ||
      (fman_mant_out == halfway && (fman_mant & 1) != 0)) {
    fman_mant++;
    if ((fman_mant & 0x000003ff) == 0) {
      fman_exp_out++;
      fman_mant = 0;
    }
  }
  *h = fsign | (fman_exp_out << 10) | fman_mant;
}