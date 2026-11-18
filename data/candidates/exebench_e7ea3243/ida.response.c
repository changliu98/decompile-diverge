void __cdecl rifft2pt(float *ioptr, float scale)
{
  float t0i; // [rsp+4h] [rbp-24h]
  float f1i; // [rsp+Ch] [rbp-1Ch]
  float f1r; // [rsp+10h] [rbp-18h]
  float f0i; // [rsp+14h] [rbp-14h]
  float f0r; // [rsp+18h] [rbp-10h]

  t0i = ioptr[1];
  f1r = 2.0 * ioptr[2];
  f1i = 2.0 * ioptr[3];
  f0r = *ioptr + t0i;
  f0i = *ioptr - t0i;
  *ioptr = scale * (float)(f0r + f1r);
  ioptr[1] = scale * (float)(f0i - f1i);
  ioptr[2] = scale * (float)(f0r - f1r);
  ioptr[3] = scale * (float)(f0i + f1i);
}