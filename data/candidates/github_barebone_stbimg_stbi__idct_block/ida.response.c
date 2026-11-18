void __cdecl stbi__idct_block(stbi_uc *out, int out_stride, short *data)
{
  int v3; // [rsp+8h] [rbp-1A8h]
  int x3_0; // [rsp+Ch] [rbp-1A4h]
  int x2_0; // [rsp+10h] [rbp-1A0h]
  int x1_0; // [rsp+14h] [rbp-19Ch]
  int x0_0; // [rsp+18h] [rbp-198h]
  int p5_0; // [rsp+1Ch] [rbp-194h]
  int p4_0; // [rsp+20h] [rbp-190h]
  int p3_0; // [rsp+24h] [rbp-18Ch]
  int p3_0a; // [rsp+24h] [rbp-18Ch]
  int p3_0b; // [rsp+24h] [rbp-18Ch]
  int p2_0; // [rsp+28h] [rbp-188h]
  int p2_0a; // [rsp+28h] [rbp-188h]
  int p1_0; // [rsp+2Ch] [rbp-184h]
  int t3_0; // [rsp+30h] [rbp-180h]
  int t3_0a; // [rsp+30h] [rbp-180h]
  int t3_0b; // [rsp+30h] [rbp-180h]
  int t2_0; // [rsp+34h] [rbp-17Ch]
  int t2_0a; // [rsp+34h] [rbp-17Ch]
  int t2_0b; // [rsp+34h] [rbp-17Ch]
  int t1_0; // [rsp+38h] [rbp-178h]
  int t1_0a; // [rsp+38h] [rbp-178h]
  int t0_0; // [rsp+3Ch] [rbp-174h]
  int t0_0a; // [rsp+3Ch] [rbp-174h]
  int x3; // [rsp+40h] [rbp-170h]
  int x2; // [rsp+44h] [rbp-16Ch]
  int x1; // [rsp+48h] [rbp-168h]
  int x0; // [rsp+4Ch] [rbp-164h]
  int p5; // [rsp+50h] [rbp-160h]
  int p4; // [rsp+54h] [rbp-15Ch]
  int p3; // [rsp+58h] [rbp-158h]
  int p3a; // [rsp+58h] [rbp-158h]
  int p3b; // [rsp+58h] [rbp-158h]
  int p2; // [rsp+5Ch] [rbp-154h]
  int p2a; // [rsp+5Ch] [rbp-154h]
  int p2b; // [rsp+5Ch] [rbp-154h]
  int p1; // [rsp+60h] [rbp-150h]
  int t3; // [rsp+64h] [rbp-14Ch]
  int t3a; // [rsp+64h] [rbp-14Ch]
  int t3b; // [rsp+64h] [rbp-14Ch]
  int t2; // [rsp+68h] [rbp-148h]
  int t2a; // [rsp+68h] [rbp-148h]
  int t2b; // [rsp+68h] [rbp-148h]
  int t1; // [rsp+6Ch] [rbp-144h]
  int t1a; // [rsp+6Ch] [rbp-144h]
  int t0; // [rsp+70h] [rbp-140h]
  int t0a; // [rsp+70h] [rbp-140h]
  short *d; // [rsp+78h] [rbp-138h]
  stbi_uc *o; // [rsp+80h] [rbp-130h]
  int *v; // [rsp+88h] [rbp-128h]
  int *va; // [rsp+88h] [rbp-128h]
  int val[64]; // [rsp+90h] [rbp-120h] BYREF
  int i; // [rsp+194h] [rbp-1Ch]
  short *dataa; // [rsp+198h] [rbp-18h]
  int out_stridea; // [rsp+1A4h] [rbp-Ch]
  stbi_uc *outa; // [rsp+1A8h] [rbp-8h]

  outa = out;
  out_stridea = out_stride;
  dataa = data;
  v = val;
  d = data;
  i = 0;
  while ( i < 8 )
  {
    if ( d[8] || d[16] || d[24] || d[32] || d[40] || d[48] || d[56] )
    {
      p2 = d[16];
      p3 = d[48];
      t2 = -7567 * p3 + 2217 * (p3 + p2);
      t3 = 3135 * p2 + 2217 * (p3 + p2);
      p2a = *d;
      p3a = d[32];
      x0 = t3 + ((p3a + p2a) << 12);
      x3 = ((p3a + p2a) << 12) - t3;
      x1 = t2 + ((p2a - p3a) << 12);
      x2 = ((p2a - p3a) << 12) - t2;
      t0 = d[56];
      t1 = d[40];
      t2a = d[24];
      t3a = d[8];
      p5 = 4816 * (t3a + t1 + t2a + t0);
      p1 = -3685 * (t3a + t0) + p5;
      p2b = -10497 * (t2a + t1) + p5;
      p3b = -8034 * (t2a + t0);
      p4 = -1597 * (t3a + t1);
      t3b = 6149 * t3a + p4 + p1;
      t2b = 12586 * t2a + p3b + p2b;
      t1a = 8410 * t1 + p4 + p2b;
      t0a = 1223 * t0 + p3b + p1;
      x0 += 512;
      x1 += 512;
      x2 += 512;
      x3 += 512;
      *v = (t3b + x0) >> 10;
      v[56] = (x0 - t3b) >> 10;
      v[8] = (t2b + x1) >> 10;
      v[48] = (x1 - t2b) >> 10;
      v[16] = (t1a + x2) >> 10;
      v[40] = (x2 - t1a) >> 10;
      v[24] = (t0a + x3) >> 10;
      v[32] = (x3 - t0a) >> 10;
    }
    else
    {
      v3 = 4 * *d;
      v[56] = v3;
      v[48] = v3;
      v[40] = v3;
      v[32] = v3;
      v[24] = v3;
      v[16] = v3;
      v[8] = v3;
      *v = v3;
    }
    ++i;
    ++d;
    ++v;
  }
  i = 0;
  va = val;
  o = outa;
  while ( i < 8 )
  {
    p2_0 = va[2];
    p3_0 = va[6];
    t2_0 = -7567 * p3_0 + 2217 * (p3_0 + p2_0);
    t3_0 = 3135 * p2_0 + 2217 * (p3_0 + p2_0);
    p3_0a = va[4];
    x0_0 = t3_0 + ((p3_0a + *va) << 12);
    x3_0 = ((p3_0a + *va) << 12) - t3_0;
    x1_0 = t2_0 + ((*va - p3_0a) << 12);
    x2_0 = ((*va - p3_0a) << 12) - t2_0;
    t0_0 = va[7];
    t1_0 = va[5];
    t2_0a = va[3];
    t3_0a = va[1];
    p5_0 = 4816 * (t3_0a + t1_0 + t2_0a + t0_0);
    p1_0 = -3685 * (t3_0a + t0_0) + p5_0;
    p2_0a = -10497 * (t2_0a + t1_0) + p5_0;
    p3_0b = -8034 * (t2_0a + t0_0);
    p4_0 = -1597 * (t3_0a + t1_0);
    t3_0b = 6149 * t3_0a + p4_0 + p1_0;
    t2_0b = 12586 * t2_0a + p3_0b + p2_0a;
    t1_0a = 8410 * t1_0 + p4_0 + p2_0a;
    t0_0a = 1223 * t0_0 + p3_0b + p1_0;
    x0_0 += 16842752;
    x1_0 += 16842752;
    x2_0 += 16842752;
    x3_0 += 16842752;
    *o = stbi__clamp((t3_0b + x0_0) >> 17);
    o[7] = stbi__clamp((x0_0 - t3_0b) >> 17);
    o[1] = stbi__clamp((t2_0b + x1_0) >> 17);
    o[6] = stbi__clamp((x1_0 - t2_0b) >> 17);
    o[2] = stbi__clamp((t1_0a + x2_0) >> 17);
    o[5] = stbi__clamp((x2_0 - t1_0a) >> 17);
    o[3] = stbi__clamp((t0_0a + x3_0) >> 17);
    o[4] = stbi__clamp((x3_0 - t0_0a) >> 17);
    ++i;
    va += 8;
    o += out_stridea;
  }
}