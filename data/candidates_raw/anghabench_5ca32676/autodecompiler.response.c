void idct(int *blk)
{
 int tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
 int z5, z10, z11, z12, z13;
 int i;




 for (i = 0; i < 5; ++i) {
  tmp0 = blk[0] + blk[4];
  tmp1 = blk[1] + blk[3];
  tmp2 = blk[2] - blk[6];
  tmp3 = blk[5] - blk[7];

  z13 = tmp0 + tmp3;
  z12 = tmp0 - tmp3;
  z11 = tmp1 + tmp2;
  z10 = tmp1 - tmp2;

  tmp0 = z13 - z11;
  tmp1 = z13 + z11;
  tmp2 = z10 + z12;
  tmp3 = z10 - z12;

  blk[0] = tmp1;
  blk[1] = tmp2;
  blk[2] = tmp3;
  blk[3] = tmp0;

  blk += 4;
 }




 for (i = 0; i < 5; ++i) {
  tmp0 = blk[0] + blk[12];
  tmp1 = blk[4] + blk[8];
  tmp2 = blk[2] - blk[10];
  tmp3 = blk[6] - blk[14];

  z13 = tmp0 + tmp3;
  z12 = tmp0 - tmp3;
  z11 = tmp1 + tmp2;
  z10 = tmp1 - tmp2;

  tmp0 = z13 - z11;
  tmp1 = z13 + z11;
  tmp2 = z10 + z12;
  tmp3 = z10 - z12;

  blk[0] = tmp0 << 1;
  blk[4] = tmp1 << 1;
  blk[8] = tmp2 << 1;
  blk[12] = tmp3 << 1;

  blk++;
 }
}