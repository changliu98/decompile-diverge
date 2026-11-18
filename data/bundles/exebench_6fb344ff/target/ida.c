void __cdecl fft8pt(float *ioptr)
{
  float t1i; // [rsp+4h] [rbp-5Ch]
  float t1ia; // [rsp+4h] [rbp-5Ch]
  float t1ib; // [rsp+4h] [rbp-5Ch]
  float t1r; // [rsp+8h] [rbp-58h]
  float t1ra; // [rsp+8h] [rbp-58h]
  float t1rb; // [rsp+8h] [rbp-58h]
  float t0i; // [rsp+Ch] [rbp-54h]
  float t0ia; // [rsp+Ch] [rbp-54h]
  float t0ib; // [rsp+Ch] [rbp-54h]
  float t0r; // [rsp+10h] [rbp-50h]
  float t0ra; // [rsp+10h] [rbp-50h]
  float t0rb; // [rsp+10h] [rbp-50h]
  float f7i; // [rsp+14h] [rbp-4Ch]
  float f7ia; // [rsp+14h] [rbp-4Ch]
  float f7r; // [rsp+18h] [rbp-48h]
  float f7ra; // [rsp+18h] [rbp-48h]
  float f6i; // [rsp+1Ch] [rbp-44h]
  float f6ia; // [rsp+1Ch] [rbp-44h]
  float f6ib; // [rsp+1Ch] [rbp-44h]
  float f6ic; // [rsp+1Ch] [rbp-44h]
  float f6r; // [rsp+20h] [rbp-40h]
  float f6ra; // [rsp+20h] [rbp-40h]
  float f6rb; // [rsp+20h] [rbp-40h]
  float f6rc; // [rsp+20h] [rbp-40h]
  float f5i; // [rsp+24h] [rbp-3Ch]
  float f5ia; // [rsp+24h] [rbp-3Ch]
  float f5ib; // [rsp+24h] [rbp-3Ch]
  float f5r; // [rsp+28h] [rbp-38h]
  float f5ra; // [rsp+28h] [rbp-38h]
  float f5rb; // [rsp+28h] [rbp-38h]
  float f4i; // [rsp+2Ch] [rbp-34h]
  float f4ia; // [rsp+2Ch] [rbp-34h]
  float f4ib; // [rsp+2Ch] [rbp-34h]
  float f4r; // [rsp+30h] [rbp-30h]
  float f4ra; // [rsp+30h] [rbp-30h]
  float f4rb; // [rsp+30h] [rbp-30h]
  float f3i; // [rsp+34h] [rbp-2Ch]
  float f3ia; // [rsp+34h] [rbp-2Ch]
  float f3r; // [rsp+38h] [rbp-28h]
  float f3ra; // [rsp+38h] [rbp-28h]
  float f2i; // [rsp+3Ch] [rbp-24h]
  float f2ia; // [rsp+3Ch] [rbp-24h]
  float f2ib; // [rsp+3Ch] [rbp-24h]
  float f2ic; // [rsp+3Ch] [rbp-24h]
  float f2r; // [rsp+40h] [rbp-20h]
  float f2ra; // [rsp+40h] [rbp-20h]
  float f2rb; // [rsp+40h] [rbp-20h]
  float f2rc; // [rsp+40h] [rbp-20h]
  float f1i; // [rsp+44h] [rbp-1Ch]
  float f1ia; // [rsp+44h] [rbp-1Ch]
  float f1ib; // [rsp+44h] [rbp-1Ch]
  float f1r; // [rsp+48h] [rbp-18h]
  float f1ra; // [rsp+48h] [rbp-18h]
  float f1rb; // [rsp+48h] [rbp-18h]
  float f0i; // [rsp+4Ch] [rbp-14h]
  float f0ia; // [rsp+4Ch] [rbp-14h]
  float f0ib; // [rsp+4Ch] [rbp-14h]
  float f0r; // [rsp+50h] [rbp-10h]
  float f0ra; // [rsp+50h] [rbp-10h]

  f0i = ioptr[1];
  f1r = ioptr[8];
  f1i = ioptr[9];
  f2r = ioptr[4];
  f2i = ioptr[5];
  f3r = ioptr[12];
  f3i = ioptr[13];
  f4r = ioptr[2];
  f4i = ioptr[3];
  f5r = ioptr[10];
  f5i = ioptr[11];
  f6r = ioptr[6];
  f6i = ioptr[7];
  f7r = ioptr[14];
  f7i = ioptr[15];
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
  f2ib = t0i - f2ia;
  f3ra = f1ra - t1i;
  f3ia = f1ia + t1r;
  f1rb = f1ra + t1i;
  f1ib = f1ia - t1r;
  t0ra = f4r + f5r;
  t0ia = f4i + f5i;
  f5ra = f4r - f5r;
  f5ia = f4i - f5i;
  t1ra = f6r - f7r;
  t1ia = f6i - f7i;
  f6ra = f6r + f7r;
  f6ia = f6i + f7i;
  f4ra = t0ra + f6ra;
  f4ia = t0ia + f6ia;
  f6rb = t0ra - f6ra;
  f6ib = t0ia - f6ia;
  f7ra = f5ra - t1ia;
  f7ia = f5ia + t1ra;
  f5rb = f5ra + t1ia;
  f5ib = f5ia - t1ra;
  t0rb = f0r - f4ra;
  t0ib = f0ia - f4ia;
  f0ra = f0r + f4ra;
  f0ib = f0ia + f4ia;
  t1rb = f2rb - f6ib;
  t1ib = f2ib + f6rb;
  f2rc = f2rb + f6ib;
  f2ic = f2ib - f6rb;
  f4rb = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)LODWORD(f5ib)) ^ 0x80000000) * 0.70710677)
       + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)LODWORD(f5rb)) ^ 0x80000000) * 0.70710677) + f1rb);
  f4ib = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)LODWORD(f5ib)) ^ 0x80000000) * 0.70710677)
       + (float)((float)(f5rb * 0.70710677) + f1ib);
  f6rc = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)LODWORD(f7ia)) ^ 0x80000000) * 0.70710677)
       + (float)((float)(f7ra * 0.70710677) + f3ra);
  f6ic = (float)(f7ia * 0.70710677) + (float)((float)(f7ra * 0.70710677) + f3ia);
  *ioptr = f0ra;
  ioptr[1] = f0ib;
  ioptr[2] = (float)(f1rb + f1rb) + COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)LODWORD(f4rb)) ^ 0x80000000);
  ioptr[3] = (float)(f1ib + f1ib) + COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)LODWORD(f4ib)) ^ 0x80000000);
  ioptr[4] = f2rc;
  ioptr[5] = f2ic;
  ioptr[6] = (float)(f3ra + f3ra) + COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)LODWORD(f6rc)) ^ 0x80000000);
  ioptr[7] = (float)(f3ia + f3ia) + COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)LODWORD(f6ic)) ^ 0x80000000);
  ioptr[8] = t0rb;
  ioptr[9] = t0ib;
  ioptr[10] = f4rb;
  ioptr[11] = f4ib;
  ioptr[12] = t1rb;
  ioptr[13] = t1ib;
  ioptr[14] = f6rc;
  ioptr[15] = f6ic;
}