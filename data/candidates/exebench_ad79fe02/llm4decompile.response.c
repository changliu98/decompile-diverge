int mpeg3video_idctcol(short *blk)
{
  int a0, a1, a2, a3, b0, b1, b2, b3, c0, c1, c2, c3, d0, d1, d2, d3;
  int e0, e1, e2, e3, f0, f1, f2, f3, tmp0, tmp1, tmp2, tmp3;
  int tmp4, tmp5, tmp6, tmp7, tmp8, tmp9, tmpa, tmpb, tmpl, tmpr;
  int i, nonzero = 0;

  for(i = 0; i < 8; i++)
    if(blk[8 * i])
      nonzero = 1;

  if(!nonzero)
  {
    blk[0] = blk[1] = blk[2] = blk[3] = blk[4] = blk[5] = blk[6] = blk[7] =
      (blk[0] + 32) >> 6;
    return 0;
  }

  a0 = blk[0] * 256 + 8192;
  a1 = blk[8] * 256;
  a2 = blk[16] * 256;
  a3 = blk[24] * 256;
  b0 = blk[32] * 256;
  b1 = blk[40] * 256;
  b2 = blk[48] * 256;
  b3 = blk[56] * 256;
  c0 = blk[64] * 256;
  c1 = blk[72] * 256;
  c2 = blk[80] * 256;
  c3 = blk[88] * 256;

  tmp0 = a0 + b0;
  tmp1 = a0 - b0;
  tmp2 = a1 + a2;
  tmp3 = a1 - a2;
  tmp4 = a3 + b3;
  tmp5 = a3 - b3;
  tmp6 = b1 + c2;
  tmp7 = b1 - c2;
  tmp8 = c0 + c3;
  tmp9 = c0 - c3;
  tmpa = b2 + c1;
  tmpb = b2 - c1;
  tmpl = tmp6 + tmpa;
  tmpr = tmp6 - tmpa;

  d0 = tmp0 + tmp8;
  d1 = tmp0 - tmp8;
  d2 = tmp1 + tmp9;
  d3 = tmp1 - tmp9;
  e0 = tmp2 + tmp4;
  e1 = tmp2 - tmp4;
  e2 = tmp3 + tmp5;
  e3 = tmp3 - tmp5;
  f0 = tmp7 + tmpr;
  f1 = tmp7 - tmpr;
  f2 = tmpb + tmpl;
  f3 = tmpb - tmpl;

  blk[0] = (d0 + e0) >> 14;
  blk[1] = (f2 + f0) >> 14;
  blk[2] = (d2 + f1) >> 14;
  blk[3] = (d3 + f3) >> 14;
  blk[4] = (d3 - f3) >> 14;
  blk[5] = (d2 - f1) >> 14;
  blk[6] = (f2 - f0) >> 14;
  blk[7] = (d0 - e0) >> 14;

  return 1;
}