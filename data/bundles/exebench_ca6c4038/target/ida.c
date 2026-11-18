void __cdecl cftf161(float *a, float *w)
{
  __m128i v2; // xmm1
  __m128i v3; // xmm1
  __m128i v4; // xmm1
  __m128i v5; // xmm1
  float y15i; // [rsp+0h] [rbp-BCh]
  float y15r; // [rsp+4h] [rbp-B8h]
  float y14i; // [rsp+8h] [rbp-B4h]
  float y14r; // [rsp+Ch] [rbp-B0h]
  float y13i; // [rsp+10h] [rbp-ACh]
  float y13r; // [rsp+14h] [rbp-A8h]
  float y12i; // [rsp+18h] [rbp-A4h]
  float y12r; // [rsp+1Ch] [rbp-A0h]
  float y11i; // [rsp+20h] [rbp-9Ch]
  float y11r; // [rsp+24h] [rbp-98h]
  float y10i; // [rsp+28h] [rbp-94h]
  float y10r; // [rsp+2Ch] [rbp-90h]
  float y9i; // [rsp+30h] [rbp-8Ch]
  float y9r; // [rsp+34h] [rbp-88h]
  float y8i; // [rsp+38h] [rbp-84h]
  float y8r; // [rsp+3Ch] [rbp-80h]
  float y7i; // [rsp+40h] [rbp-7Ch]
  float y7r; // [rsp+44h] [rbp-78h]
  float y6i; // [rsp+48h] [rbp-74h]
  float y6r; // [rsp+4Ch] [rbp-70h]
  float y5i; // [rsp+50h] [rbp-6Ch]
  float y5r; // [rsp+54h] [rbp-68h]
  float y4i; // [rsp+58h] [rbp-64h]
  float y4r; // [rsp+5Ch] [rbp-60h]
  float y3i; // [rsp+60h] [rbp-5Ch]
  float y3r; // [rsp+64h] [rbp-58h]
  float y2i; // [rsp+68h] [rbp-54h]
  float y2r; // [rsp+6Ch] [rbp-50h]
  float y1i; // [rsp+70h] [rbp-4Ch]
  float y1r; // [rsp+74h] [rbp-48h]
  float y0i; // [rsp+78h] [rbp-44h]
  float y0r; // [rsp+7Ch] [rbp-40h]
  float x3i; // [rsp+80h] [rbp-3Ch]
  float x3ia; // [rsp+80h] [rbp-3Ch]
  float x3ib; // [rsp+80h] [rbp-3Ch]
  float x3ic; // [rsp+80h] [rbp-3Ch]
  float x3id; // [rsp+80h] [rbp-3Ch]
  float x3r; // [rsp+84h] [rbp-38h]
  float x3ra; // [rsp+84h] [rbp-38h]
  float x3rb; // [rsp+84h] [rbp-38h]
  float x3rc; // [rsp+84h] [rbp-38h]
  float x3rd; // [rsp+84h] [rbp-38h]
  float x2i; // [rsp+88h] [rbp-34h]
  float x2ia; // [rsp+88h] [rbp-34h]
  float x2ib; // [rsp+88h] [rbp-34h]
  float x2ic; // [rsp+88h] [rbp-34h]
  float x2id; // [rsp+88h] [rbp-34h]
  float x2r; // [rsp+8Ch] [rbp-30h]
  float x2ra; // [rsp+8Ch] [rbp-30h]
  float x2rb; // [rsp+8Ch] [rbp-30h]
  float x2rc; // [rsp+8Ch] [rbp-30h]
  float x2rd; // [rsp+8Ch] [rbp-30h]
  float x1i; // [rsp+90h] [rbp-2Ch]
  float x1ia; // [rsp+90h] [rbp-2Ch]
  float x1ib; // [rsp+90h] [rbp-2Ch]
  float x1ic; // [rsp+90h] [rbp-2Ch]
  float x1r; // [rsp+94h] [rbp-28h]
  float x1ra; // [rsp+94h] [rbp-28h]
  float x1rb; // [rsp+94h] [rbp-28h]
  float x1rc; // [rsp+94h] [rbp-28h]
  float x0i; // [rsp+98h] [rbp-24h]
  float x0ia; // [rsp+98h] [rbp-24h]
  float x0ib; // [rsp+98h] [rbp-24h]
  float x0ic; // [rsp+98h] [rbp-24h]
  float x0r; // [rsp+9Ch] [rbp-20h]
  float x0ra; // [rsp+9Ch] [rbp-20h]
  float x0rb; // [rsp+9Ch] [rbp-20h]
  float x0rc; // [rsp+9Ch] [rbp-20h]
  float wk1i; // [rsp+A0h] [rbp-1Ch]
  float wk1r; // [rsp+A4h] [rbp-18h]
  float wn4r; // [rsp+A8h] [rbp-14h]

  wn4r = w[1];
  wk1r = w[2];
  wk1i = w[3];
  x0r = *a + a[16];
  x0i = a[1] + a[17];
  x1r = *a - a[16];
  x1i = a[1] - a[17];
  x2r = a[8] + a[24];
  x2i = a[9] + a[25];
  x3r = a[8] - a[24];
  x3i = a[9] - a[25];
  y0r = x0r + x2r;
  y0i = x0i + x2i;
  y4r = x0r - x2r;
  y4i = x0i - x2i;
  y8r = x1r - x3i;
  y8i = x1i + x3r;
  y12r = x1r + x3i;
  y12i = x1i - x3r;
  x0ra = a[2] + a[18];
  x0ia = a[3] + a[19];
  x1ra = a[2] - a[18];
  x1ia = a[3] - a[19];
  x2ra = a[10] + a[26];
  x2ia = a[11] + a[27];
  x3ra = a[10] - a[26];
  x3ia = a[11] - a[27];
  y1r = x0ra + x2ra;
  y1i = x0ia + x2ia;
  y5r = x0ra - x2ra;
  y5i = x0ia - x2ia;
  v2 = (__m128i)LODWORD(wk1i);
  *(float *)v2.m128i_i32 = wk1i * (float)(x1ia + x3ra);
  y9r = (float)(wk1r * (float)(x1ra - x3ia)) + COERCE_FLOAT(_mm_cvtsi128_si32(v2) ^ 0x80000000);
  y9i = (float)(wk1r * (float)(x1ia + x3ra)) + (float)(wk1i * (float)(x1ra - x3ia));
  v3 = (__m128i)LODWORD(wk1r);
  *(float *)v3.m128i_i32 = wk1r * (float)(x1ia - x3ra);
  y13r = (float)(wk1i * (float)(x1ra + x3ia)) + COERCE_FLOAT(_mm_cvtsi128_si32(v3) ^ 0x80000000);
  y13i = (float)(wk1i * (float)(x1ia - x3ra)) + (float)(wk1r * (float)(x1ra + x3ia));
  x0rb = a[4] + a[20];
  x0ib = a[5] + a[21];
  x1rb = a[4] - a[20];
  x1ib = a[5] - a[21];
  x2rb = a[12] + a[28];
  x2ib = a[13] + a[29];
  x3rb = a[12] - a[28];
  x3ib = a[13] - a[29];
  y2r = x0rb + x2rb;
  y2i = x0ib + x2ib;
  y6r = x0rb - x2rb;
  y6i = x0ib - x2ib;
  y10r = wn4r * (float)((float)(x1rb - x3ib) - (float)(x1ib + x3rb));
  y10i = wn4r * (float)((float)(x1ib + x3rb) + (float)(x1rb - x3ib));
  y14r = wn4r * (float)((float)(x1rb + x3ib) + (float)(x1ib - x3rb));
  y14i = wn4r * (float)((float)(x1ib - x3rb) - (float)(x1rb + x3ib));
  x0rc = a[6] + a[22];
  x0ic = a[7] + a[23];
  x1rc = a[6] - a[22];
  x1ic = a[7] - a[23];
  x2rc = a[14] + a[30];
  x2ic = a[15] + a[31];
  x3rc = a[14] - a[30];
  x3ic = a[15] - a[31];
  y3r = x0rc + x2rc;
  y3i = x0ic + x2ic;
  y7r = x0rc - x2rc;
  y7i = x0ic - x2ic;
  v4 = (__m128i)LODWORD(wk1r);
  *(float *)v4.m128i_i32 = wk1r * (float)(x1ic + x3rc);
  y11r = (float)(wk1i * (float)(x1rc - x3ic)) + COERCE_FLOAT(_mm_cvtsi128_si32(v4) ^ 0x80000000);
  y11i = (float)(wk1i * (float)(x1ic + x3rc)) + (float)(wk1r * (float)(x1rc - x3ic));
  v5 = (__m128i)LODWORD(wk1i);
  *(float *)v5.m128i_i32 = wk1i * (float)(x1ic - x3rc);
  y15r = (float)(wk1r * (float)(x1rc + x3ic)) + COERCE_FLOAT(_mm_cvtsi128_si32(v5) ^ 0x80000000);
  y15i = (float)(wk1r * (float)(x1ic - x3rc)) + (float)(wk1i * (float)(x1rc + x3ic));
  a[24] = (float)(y12r - y14r) + (float)(y13r - y15r);
  a[25] = (float)(y12i - y14i) + (float)(y13i - y15i);
  a[26] = (float)(y12r - y14r) - (float)(y13r - y15r);
  a[27] = (float)(y12i - y14i) - (float)(y13i - y15i);
  a[28] = (float)(y12r + y14r) - (float)(y13i + y15i);
  a[29] = (float)(y12i + y14i) + (float)(y13r + y15r);
  a[30] = (float)(y12r + y14r) + (float)(y13i + y15i);
  a[31] = (float)(y12i + y14i) - (float)(y13r + y15r);
  a[16] = (float)(y8r + y10r) + (float)(y9r + y11r);
  a[17] = (float)(y8i + y10i) + (float)(y9i + y11i);
  a[18] = (float)(y8r + y10r) - (float)(y9r + y11r);
  a[19] = (float)(y8i + y10i) - (float)(y9i + y11i);
  a[20] = (float)(y8r - y10r) - (float)(y9i - y11i);
  a[21] = (float)(y8i - y10i) + (float)(y9r - y11r);
  a[22] = (float)(y8r - y10r) + (float)(y9i - y11i);
  a[23] = (float)(y8i - y10i) - (float)(y9r - y11r);
  x2rd = wn4r * (float)((float)(y5r - (float)(x0ic - x2ic)) - (float)(y5i + (float)(x0rc - x2rc)));
  x2id = wn4r * (float)((float)(y5i + y7r) + (float)(y5r - (float)(x0ic - x2ic)));
  x3rd = wn4r * (float)((float)(y5r + y7i) - (float)(y5i - y7r));
  x3id = wn4r * (float)((float)(y5i - y7r) + (float)(y5r + y7i));
  a[8] = (float)(y4r - y6i) + x2rd;
  a[9] = (float)(y4i + y6r) + x2id;
  a[10] = (float)(y4r - y6i) - x2rd;
  a[11] = (float)(y4i + y6r) - x2id;
  a[12] = (float)(y4r + y6i) - x3id;
  a[13] = (float)(y4i - y6r) + x3rd;
  a[14] = (float)(y4r + y6i) + x3id;
  a[15] = (float)(y4i - y6r) - x3rd;
  *a = (float)(y0r + y2r) + (float)(y1r + y3r);
  a[1] = (float)(y0i + y2i) + (float)(y1i + y3i);
  a[2] = (float)(y0r + y2r) - (float)(y1r + y3r);
  a[3] = (float)(y0i + y2i) - (float)(y1i + y3i);
  a[4] = (float)(y0r - y2r) - (float)(y1i - y3i);
  a[5] = (float)(y0i - y2i) + (float)(y1r - y3r);
  a[6] = (float)(y0r - y2r) + (float)(y1i - y3i);
  a[7] = (float)(y0i - y2i) - (float)(y1r - y3r);
}