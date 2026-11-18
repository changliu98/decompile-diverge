void plm_video_idct(int *blk)
{
 int tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
 int z5, z10, z11, z12, z13;
 int i;

 for (i = 0; i < 8; ++i) {
  z10 = blk[4 * 8 + i] + blk[6 * 8 + i];
  z11 = blk[2 * 8 + i] + blk[7 * 8 + i];
  z12 = blk[5 * 8 + i] - blk[3 * 8 + i];
  tmp0 = blk[1 * 8 + i] + blk[7 * 8 + i];
  tmp1 = blk[3 * 8 + i] + blk[5 * 8 + i];
  tmp2 = blk[1 * 8 + i] - blk[7 * 8 + i];
  tmp3 = tmp0 + tmp1;
  tmp4 = blk[0 * 8 + i];
  tmp5 = (((tmp2) * ((int)((1.1020)*256+0.5)) - (z12) * ((int)((2.0306)*256+0.5)) + (1 << (8 - 1))) >> (8)) - tmp3;
  tmp6 = tmp5 - (((tmp0 - tmp1) * ((int)((1.4142)*256+0.5)) + (1 << (8 - 1))) >> (8));
  tmp7 = tmp4 - z10;
  z13 = (((blk[2 * 8 + i] - blk[6 * 8 + i]) * ((int)((1.4142)*256+0.5)) + (1 << (8 - 1))) >> (8)) - z11;
  z5 = tmp4 + z10;
  tmp0 = tmp7 + z13;
  tmp1 = z5 + z11;
  tmp2 = tmp7 - z13;
  tmp3 = z5 - z11;
  tmp4 = -tmp6 - (((z12) * ((int)((2.0306)*256+0.5)) + (tmp2) * ((int)((1.1020)*256+0.5)) + (1 << (8 - 1))) >> (8));
  blk[0 * 8 + i] = (tmp3 + tmp1);
  blk[1 * 8 + i] = (tmp5 + tmp0);
  blk[2 * 8 + i] = (tmp2 - tmp6);
  blk[3 * 8 + i] = (tmp3 - tmp4);
  blk[4 * 8 + i] = (tmp3 + tmp4);
  blk[5 * 8 + i] = (tmp2 + tmp6);
  blk[6 * 8 + i] = (tmp0 - tmp5);
  blk[7 * 8 + i] = (tmp1 - tmp3);
 }

 for (i = 0; i < 64; i += 8) {
  z10 = blk[4 + i] + blk[6 + i];
  z11 = blk[2 + i] + blk[7 + i];
  z12 = blk[5 + i] - blk[3 + i];
  tmp0 = blk[1 + i] + blk[7 + i];
  tmp1 = blk[3 + i] + blk[5 + i];
  tmp2 = blk[1 + i] - blk[7 + i];
  tmp3 = tmp0 + tmp1;
  tmp4 = blk[i];
  tmp5 = (((tmp2) * ((int)((1.1020)*256+0.5)) - (z12) * ((int)((2.0306)*256+0.5)) + (1 << (8 - 1))) >> (8)) - tmp3;
  tmp6 = tmp5 - (((tmp0 - tmp1) * ((int)((1.4142)*256+0.5)) + (1 << (8 - 1))) >> (8));
  tmp7 = tmp4 - z10;
  z13 = (((blk[2 + i] - blk[6 + i]) * ((int)((1.4142)*256+0.5)) + (1 << (8 - 1))) >> (8)) - z11;
  z5 = tmp4 + z10;
  tmp0 = tmp7 + z13;
  tmp1 = z5 + z11;
  tmp2 = tmp7 - z13;
  tmp3 = z5 - z11;
  tmp4 = -tmp6 - (((z12) * ((int)((2.0306)*256+0.5)) + (tmp2) * ((int)((1.1020)*256+0.5)) + (1 << (8 - 1))) >> (8));
  blk[i] = (((tmp3 + tmp1) + (1 << (8 - 1))) >> (8));
  blk[1 + i] = (((tmp5 + tmp0) + (1 << (8 - 1))) >> (8));
  blk[2 + i] = (((tmp2 - tmp6) + (1 << (8 - 1))) >> (8));
  blk[3 + i] = (((tmp3 - tmp4) + (1 << (8 - 1))) >> (8));
  blk[4 + i] = (((tmp3 + tmp4) + (1 << (8 - 1))) >> (8));
  blk[5 + i] = (((tmp2 + tmp6) + (1 << (8 - 1))) >> (8));
  blk[6 + i] = (((tmp0 - tmp5) + (1 << (8 - 1))) >> (8));
  blk[7 + i] = (((tmp1 - tmp3) + (1 << (8 - 1))) >> (8));
 }
}