void htonld(double *d)
{
  union { double d; unsigned char b[8]; } u;
  u.d = *d;
  u.b[0] = (unsigned char)(u.d >> 56);
  u.b[1] = (unsigned char)(u.d >> 48);
  u.b[2] = (unsigned char)(u.d >> 40);
  u.b[3] = (unsigned char)(u.d >> 32);
  u.b[4] = (unsigned char)(u.d >> 24);
  u.b[5] = (unsigned char)(u.d >> 16);
  u.b[6] = (unsigned char)(u.d >> 8);
  u.b[7] = (unsigned char)(u.d);
  *d = u.d;
}