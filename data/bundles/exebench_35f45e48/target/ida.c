void __cdecl fft4pt(float *ioptr)
{
  float t1i; // [rsp+0h] [rbp-38h]
  float t1r; // [rsp+4h] [rbp-34h]
  float t0i; // [rsp+8h] [rbp-30h]
  float t0r; // [rsp+Ch] [rbp-2Ch]
  float f3i; // [rsp+10h] [rbp-28h]
  float f3r; // [rsp+14h] [rbp-24h]
  float f2i; // [rsp+18h] [rbp-20h]
  float f2ia; // [rsp+18h] [rbp-20h]
  float f2r; // [rsp+1Ch] [rbp-1Ch]
  float f2ra; // [rsp+1Ch] [rbp-1Ch]
  float f1i; // [rsp+20h] [rbp-18h]
  float f1ia; // [rsp+20h] [rbp-18h]
  float f1r; // [rsp+24h] [rbp-14h]
  float f1ra; // [rsp+24h] [rbp-14h]
  float f0i; // [rsp+28h] [rbp-10h]

  f0i = ioptr[1];
  f1r = ioptr[4];
  f1i = ioptr[5];
  f2r = ioptr[2];
  f2i = ioptr[3];
  f3r = ioptr[6];
  f3i = ioptr[7];
  t0r = *ioptr + f1r;
  t0i = f0i + f1i;
  f1ra = *ioptr - f1r;
  f1ia = f0i - f1i;
  t1r = f2r - f3r;
  t1i = f2i - f3i;
  f2ra = f2r + f3r;
  f2ia = f2i + f3i;
  *ioptr = t0r + f2ra;
  ioptr[1] = t0i + f2ia;
  ioptr[2] = f1ra + t1i;
  ioptr[3] = f1ia - t1r;
  ioptr[4] = t0r - f2ra;
  ioptr[5] = t0i - f2ia;
  ioptr[6] = f1ra - t1i;
  ioptr[7] = f1ia + t1r;
}