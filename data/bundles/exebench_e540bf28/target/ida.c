void __cdecl rfft1pt(float *ioptr)
{
  float t0i; // [rsp+0h] [rbp-18h]
  float f0i; // [rsp+8h] [rbp-10h]

  f0i = ioptr[1];
  t0i = *ioptr - f0i;
  *ioptr = *ioptr + f0i;
  ioptr[1] = t0i;
}