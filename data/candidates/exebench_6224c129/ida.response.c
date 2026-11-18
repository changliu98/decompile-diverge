void __cdecl fft2pt(float *ioptr)
{
  float t0r; // [rsp+4h] [rbp-1Ch]
  float f1i; // [rsp+8h] [rbp-18h]
  float f1r; // [rsp+Ch] [rbp-14h]
  float f1ra; // [rsp+Ch] [rbp-14h]
  float f0i; // [rsp+10h] [rbp-10h]

  f0i = ioptr[1];
  f1r = ioptr[2];
  f1i = ioptr[3];
  t0r = *ioptr + f1r;
  f1ra = *ioptr - f1r;
  *ioptr = t0r;
  ioptr[1] = f0i + f1i;
  ioptr[2] = f1ra;
  ioptr[3] = f0i - f1i;
}