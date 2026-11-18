void fltrep_float_to_half(float *f, unsigned short *h) {
# 100 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/lebedevRI/darktable/refs/heads/master/src/common/half.c"
  unsigned int f32 = *(unsigned int *)f;
  unsigned int f32abs = f32 & 0x7fffffffU;
  if (f32abs > 0x7f800000U) {

    *h = 0x7fffU;
    return;
  }
  unsigned int sign = f32 & 0x80000000U;
  unsigned int exponent;
  unsigned int mantissa;
  if (f32abs >= 0x47800000U) {

    *h = ((sign >> 16) | 0x7c00U);
    return;
  } else if (f32abs < 0x33000002U) {

    *h = ((sign >> 16) | 0U);
    return;
  }
  exponent = (f32abs >> 23) & 0xffU;
  mantissa = f32abs & 0x7fffffU;
  int shift;
  if (exponent > 0x70U) {

    shift = 13;
    exponent -= 0x70U;
  } else {

    shift = 0x7eU - exponent;
    exponent = 0;
    mantissa |= 0x800000U;
  }
  unsigned int lsb = 1 << shift;
  unsigned int lsb_s1 = lsb >> 1;
  unsigned int lsb_m1 = lsb - 1;
  unsigned int remainder = mantissa & lsb_m1;
  mantissa >>= shift;
  if ((remainder > lsb_s1) || ((remainder == lsb_s1) && (mantissa & 0x01))) {

    mantissa += 1;
    if (mantissa & 0x03ff) {

    } else if (mantissa & 0x0400) {

      exponent += 1;
      mantissa = 0;
    }
  }
  *h = (unsigned short)((sign >> 16) | (exponent << 10) | mantissa);

}