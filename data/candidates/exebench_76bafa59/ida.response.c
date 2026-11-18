void __cdecl rifft1pt(float *ioptr, float scale)
{
  float t0i; // [rsp+0h] [rbp-1Ch]
  float f0i; // [rsp+8h] [rbp-14h]

  f0i = ioptr[1];
  t0i = *ioptr - f0i;
  *ioptr = scale * (float)(*ioptr + f0i);
  ioptr[1] = scale * t0i;
}