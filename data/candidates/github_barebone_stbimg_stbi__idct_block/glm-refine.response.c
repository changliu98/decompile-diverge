void __cdecl stbi__idct_block(stbi_uc *out, int out_stride, short *data)
{
  int val[64];
  int i;

  // 1D IDCT: Horizontal pass (rows)
  for (i = 0; i < 8; ++i)
  {
    int *v = &val[i * 8];
    short *d = &data[i * 8];

    // Check if AC coefficients are all zero
    if (d[8] || d[16] || d[24] || d[32] || d[40] || d[48] || d[56])
    {
      int p2 = d[16];
      int p3 = d[48];
      int t2 = -7567 * p3 + 2217 * (p3 + p2);
      int t3 = 3135 * p2 + 2217 * (p3 + p2);
      
      int p2a = d[0];
      int p3a = d[32];
      int x0 = t3 + ((p3a + p2a) << 12);
      int x3 = ((p3a + p2a) << 12) - t3;
      int x1 = t2 + ((p2a - p3a) << 12);
      int x2 = ((p2a - p3a) << 12) - t2;
      
      int t0 = d[56];
      int t1 = d[40];
      int t2a = d[24];
      int t3a = d[8];
      
      int p5 = 4816 * (t3a + t1 + t2a + t0);
      int p1 = -3685 * (t3a + t0) + p5;
      int p2b = -10497 * (t2a + t1) + p5;
      int p3b = -8034 * (t2a + t0);
      int p4 = -1597 * (t3a + t1);
      
      int t3b = 6149 * t3a + p4 + p1;
      int t2b = 12586 * t2a + p3b + p2b;
      int t1a = 8410 * t1 + p4 + p2b;
      int t0a = 1223 * t0 + p3b + p1;
      
      x0 += 512;
      x1 += 512;
      x2 += 512;
      x3 += 512;
      
      v[0]  = (t3b + x0) >> 10;
      v[56] = (x0 - t3b) >> 10;
      v[8]  = (t2b + x1) >> 10;
      v[48] = (x1 - t2b) >> 10;
      v[16] = (t1a + x2) >> 10;
      v[40] = (x2 - t1a) >> 10;
      v[24] = (t0a + x3) >> 10;
      v[32] = (x3 - t0a) >> 10;
    }
    else
    {
      // Fast path: DC coefficient only
      int v3 = (*d) << 12; // Equivalent to 4 * *d
      v[0]  = v3;
      v[8]  = v3;
      v[16] = v3;
      v[24] = v3;
      v[32] = v3;
      v[40] = v3;
      v[48] = v3;
      v[56] = v3;
    }
  }

  // 1D IDCT: Vertical pass (columns)
  for (i = 0; i < 8; ++i)
  {
    stbi_uc *o = &out[i * out_stride];
    int *va = &val[i];

    int p2 = va[2];
    int p3 = va[6];
    int t2 = -7567 * p3 + 2217 * (p3 + p2);
    int t3 = 3135 * p2 + 2217 * (p3 + p2);
    
    int p3a = va[4];
    int x0 = t3 + ((p3a + va[0]) << 12);
    int x3 = ((p3a + va[0]) << 12) - t3;
    int x1 = t2 + ((va[0] - p3a) << 12);
    int x2 = ((va[0] - p3a) << 12) - t2;
    
    int t0 = va[7];
    int t1 = va[5];
    int t2a = va[3];
    int t3a = va[1];
    
    int p5 = 4816 * (t3a + t1 + t2a + t0);
    int p1 = -3685 * (t3a + t0) + p5;
    int p2b = -10497 * (t2a + t1) + p5;
    int p3b = -8034 * (t2a + t0);
    int p4 = -1597 * (t3a + t1);
    
    int t3b = 6149 * t3a + p4 + p1;
    int t2b = 12586 * t2a + p3b + p2b;
    int t1a = 8410 * t1 + p4 + p2b;
    int t0a = 1223 * t0 + p3b + p1;
    
    // 16842752 is (512 << 15), acting as the +512 rounding offset before the >> 17 shift
    x0 += 16842752;
    x1 += 16842752;
    x2 += 16842752;
    x3 += 16842752;
    
    o[0] = stbi__clamp((t3b + x0) >> 17);
    o[7] = stbi__clamp((x0 - t3b) >> 17);
    o[1] = stbi__clamp((t2b + x1) >> 17);
    o[6] = stbi__clamp((x1 - t2b) >> 17);
    o[2] = stbi__clamp((t1a + x2) >> 17);
    o[5] = stbi__clamp((x2 - t1a) >> 17);
    o[3] = stbi__clamp((t0a + x3) >> 17);
    o[4] = stbi__clamp((x3 - t0a) >> 17);
  }
}