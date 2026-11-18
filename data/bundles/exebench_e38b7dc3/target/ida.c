void __cdecl rfft4pt(float *ioptr)
{
  float t1i; // [rsp+Ch] [rbp-38h]
  float t1ia; // [rsp+Ch] [rbp-38h]
  float t1r; // [rsp+10h] [rbp-34h]
  float t1ra; // [rsp+10h] [rbp-34h]
  float t0i; // [rsp+14h] [rbp-30h]
  float t0ia; // [rsp+14h] [rbp-30h]
  float t0r; // [rsp+18h] [rbp-2Ch]
  float t0ra; // [rsp+18h] [rbp-2Ch]
  float f3i; // [rsp+1Ch] [rbp-28h]
  float f3ia; // [rsp+1Ch] [rbp-28h]
  float f3r; // [rsp+20h] [rbp-24h]
  float f3ra; // [rsp+20h] [rbp-24h]
  float f2i; // [rsp+24h] [rbp-20h]
  float f2ia; // [rsp+24h] [rbp-20h]
  float f2ib; // [rsp+24h] [rbp-20h]
  float f2r; // [rsp+28h] [rbp-1Ch]
  float f2ra; // [rsp+28h] [rbp-1Ch]
  float f2rb; // [rsp+28h] [rbp-1Ch]
  float f1i; // [rsp+2Ch] [rbp-18h]
  float f1ia; // [rsp+2Ch] [rbp-18h]
  float f1ib; // [rsp+2Ch] [rbp-18h]
  float f1ic; // [rsp+2Ch] [rbp-18h]
  float f1r; // [rsp+30h] [rbp-14h]
  float f1ra; // [rsp+30h] [rbp-14h]
  float f1rb; // [rsp+30h] [rbp-14h]
  float f1rc; // [rsp+30h] [rbp-14h]
  float f0i; // [rsp+34h] [rbp-10h]
  float f0ia; // [rsp+34h] [rbp-10h]
  float f0ib; // [rsp+34h] [rbp-10h]
  float f0r; // [rsp+38h] [rbp-Ch]

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
  f0r = t0r + f2ra;
  f0ia = t0i + f2ia;
  f2rb = t0r - f2ra;
  f2ib = f2ia - t0i;
  f3ra = f1ra - t1i;
  f3ia = f1ia + t1r;
  f1rb = f1ra + t1i;
  f1ib = f1ia - t1r;
  t0ra = f0r + f0ia;
  t0ia = f0r - f0ia;
  t1ra = f1rb + f3ra;
  t1ia = f1ib - f3ia;
  f0ib = f3ra - f1rb;
  f1rc = (float)(0.70710677 * (float)(f3ra - f1rb))
       + (float)((float)(0.70710677 * (float)(f1ib + f3ia)) + (float)(f1rb + f3ra));
  f1ic = (float)(0.70710677 * f0ib)
       + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)0x3F3504F3u) ^ 0x80000000) * (float)(f1ib + f3ia))
               + (float)(f1ib - f3ia));
  ioptr[4] = f2rb;
  ioptr[5] = f2ib;
  *ioptr = t0ra;
  ioptr[1] = t0ia;
  ioptr[2] = 0.5 * f1rc;
  ioptr[3] = 0.5 * f1ic;
  ioptr[6] = 0.5 * (float)((float)(t1ra + t1ra) + COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)LODWORD(f1rc)) ^ 0x80000000));
  ioptr[7] = 0.5 * (float)(f1ic - (float)(t1ia + t1ia));
}