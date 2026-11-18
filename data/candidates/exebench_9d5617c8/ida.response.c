void __cdecl ifft2pt(float *ioptr, float scale)
{
  float t0r; // [rsp+4h] [rbp-20h]
  float f1i; // [rsp+8h] [rbp-1Ch]
  float f1r; // [rsp+Ch] [rbp-18h]
  float f1ra; // [rsp+Ch] [rbp-18h]
  float f0i; // [rsp+10h] [rbp-14h]

  f0i = ioptr[1];
  f1r = ioptr[2];
  f1i = ioptr[3];
  t0r = *ioptr + f1r;
  f1ra = *ioptr - f1r;
  *ioptr = scale * t0r;
  ioptr[1] = scale * (float)(f0i + f1i);
  ioptr[2] = scale * f1ra;
  ioptr[3] = scale * (float)(f0i - f1i);
}