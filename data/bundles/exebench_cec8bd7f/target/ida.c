void __cdecl cftf082(float *a)
{
  __m128i v1; // xmm1
  __m128i v2; // xmm1
  __m128i v3; // xmm1
  __m128i v4; // xmm1
  float y7i; // [rsp+0h] [rbp-64h]
  float y7r; // [rsp+4h] [rbp-60h]
  float y6i; // [rsp+8h] [rbp-5Ch]
  float y6r; // [rsp+Ch] [rbp-58h]
  float y5i; // [rsp+10h] [rbp-54h]
  float y5r; // [rsp+14h] [rbp-50h]
  float y4i; // [rsp+18h] [rbp-4Ch]
  float y4r; // [rsp+1Ch] [rbp-48h]
  float y3i; // [rsp+20h] [rbp-44h]
  float y3r; // [rsp+24h] [rbp-40h]
  float y2i; // [rsp+28h] [rbp-3Ch]
  float y2r; // [rsp+2Ch] [rbp-38h]
  float y1i; // [rsp+30h] [rbp-34h]
  float y1r; // [rsp+34h] [rbp-30h]
  float y0i; // [rsp+38h] [rbp-2Ch]
  float y0r; // [rsp+3Ch] [rbp-28h]
  float x0i; // [rsp+48h] [rbp-1Ch]
  float x0ia; // [rsp+48h] [rbp-1Ch]
  float x0ib; // [rsp+48h] [rbp-1Ch]
  float x0ic; // [rsp+48h] [rbp-1Ch]
  float x0id; // [rsp+48h] [rbp-1Ch]
  float x0ie; // [rsp+48h] [rbp-1Ch]
  float x0r; // [rsp+4Ch] [rbp-18h]
  float x0ra; // [rsp+4Ch] [rbp-18h]
  float x0rb; // [rsp+4Ch] [rbp-18h]
  float x0rc; // [rsp+4Ch] [rbp-18h]
  float x0rd; // [rsp+4Ch] [rbp-18h]
  float x0re; // [rsp+4Ch] [rbp-18h]

  y0r = *a - a[9];
  y0i = a[1] + a[8];
  y1r = *a + a[9];
  y1i = a[1] - a[8];
  x0r = a[4] - a[13];
  x0i = a[5] + a[12];
  y2r = 0.70710677 * (float)(x0r - x0i);
  y2i = 0.70710677 * (float)(x0i + x0r);
  x0ra = a[4] + a[13];
  x0ia = a[5] - a[12];
  y3r = 0.70710677 * (float)(x0ra - x0ia);
  y3i = 0.70710677 * (float)(x0ia + x0ra);
  x0rb = a[2] - a[11];
  x0ib = a[3] + a[10];
  v1 = (__m128i)0x3EC3EF15u;
  *(float *)v1.m128i_i32 = 0.38268343 * x0ib;
  y4r = (float)(0.9238795 * x0rb) + COERCE_FLOAT(_mm_cvtsi128_si32(v1) ^ 0x80000000);
  y4i = (float)(0.9238795 * x0ib) + (float)(0.38268343 * x0rb);
  x0rc = a[2] + a[11];
  x0ic = a[3] - a[10];
  v2 = (__m128i)0x3F6C835Eu;
  *(float *)v2.m128i_i32 = 0.9238795 * x0ic;
  y5r = (float)(0.38268343 * x0rc) + COERCE_FLOAT(_mm_cvtsi128_si32(v2) ^ 0x80000000);
  y5i = (float)(0.38268343 * x0ic) + (float)(0.9238795 * x0rc);
  x0rd = a[6] - a[15];
  x0id = a[7] + a[14];
  v3 = (__m128i)0x3F6C835Eu;
  *(float *)v3.m128i_i32 = 0.9238795 * x0id;
  y6r = (float)(0.38268343 * x0rd) + COERCE_FLOAT(_mm_cvtsi128_si32(v3) ^ 0x80000000);
  y6i = (float)(0.38268343 * x0id) + (float)(0.9238795 * x0rd);
  x0re = a[6] + a[15];
  x0ie = a[7] - a[14];
  v4 = (__m128i)0x3EC3EF15u;
  *(float *)v4.m128i_i32 = 0.38268343 * x0ie;
  y7r = (float)(0.9238795 * x0re) + COERCE_FLOAT(_mm_cvtsi128_si32(v4) ^ 0x80000000);
  y7i = (float)(0.9238795 * x0ie) + (float)(0.38268343 * x0re);
  *a = (float)(y0r + y2r) + (float)(y4r + y6r);
  a[1] = (float)(y0i + y2i) + (float)(y4i + y6i);
  a[2] = (float)(y0r + y2r) - (float)(y4r + y6r);
  a[3] = (float)(y0i + y2i) - (float)(y4i + y6i);
  a[4] = (float)(y0r - y2r) - (float)(y4i - y6i);
  a[5] = (float)(y0i - y2i) + (float)(y4r - y6r);
  a[6] = (float)(y0r - y2r) + (float)(y4i - y6i);
  a[7] = (float)(y0i - y2i) - (float)(y4r - y6r);
  a[8] = (float)(y1r - y3i) + (float)(y5r - y7r);
  a[9] = (float)(y1i + y3r) + (float)(y5i - y7i);
  a[10] = (float)(y1r - y3i) - (float)(y5r - y7r);
  a[11] = (float)(y1i + y3r) - (float)(y5i - y7i);
  a[12] = (float)(y1r + y3i) - (float)(y5i + y7i);
  a[13] = (float)(y1i - y3r) + (float)(y5r + y7r);
  a[14] = (float)(y1r + y3i) + (float)(y5i + y7i);
  a[15] = (float)(y1i - y3r) - (float)(y5r + y7r);
}