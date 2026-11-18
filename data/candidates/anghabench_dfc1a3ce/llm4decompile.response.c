void TH_float2halfbits(float *src, unsigned short *dest)
{
  float f;
  unsigned int *u;
  unsigned int s;
  unsigned int e;
  unsigned int m;
  unsigned int sn;
  unsigned int em;
  unsigned int shift;
  unsigned int lsb;
  unsigned int lsb_s1;
  unsigned int lsb_m1;
  unsigned int remainder;
  unsigned int half;

  f = *src;
  u = (unsigned int *)(&f);
  s = *u;

  sn = s & 0x80000000;
  e = s & 0x7f800000;
  m = s & 0x007fffff;


  if (e >= 0x7f800000) {
    half = sn | 0x7fff;
    *dest = half;
    return;
  }


  if (e >= 0x477ff000) {
    half = sn | 0x7c00;
    *dest = half;
    return;
  }


  if (e <= 0x33000000) {
    half = sn;
    *dest = half;
    return;
  }


  e = e >> 23;


  if (e > 112) {
    shift = 13;
    em = e - 112;
  } else {
    shift = 126 - e;
    em = 0;
    m = m | 0x00800000;
  }


  lsb = 1 << shift;
  lsb_s1 = lsb >> 1;
  lsb_m1 = lsb - 1;


  remainder = m & lsb_m1;


  m = m >> shift;


  if (remainder > lsb_s1 || ((remainder == lsb_s1) && (m & 1))) {
    m += 1;
    if (m & 0x003ff) {
      m = m;
    } else {
      m = 0;
      em += 1;
    }
  }

  half = sn | (em << 10) | m;
  *dest = half;
  return;
}