int mpeg3video_idctrow(short *blk)
{
 int x0, x1, x2, x3, x4, x5, x6, x7, tmp;
 int z5, z10, z11, z12, z13;
 int i;

 if (!((x1 = blk[8*4] << 8) | (x2 = blk[8*6]) | (x3 = blk[8*2]) |
          (x4 = blk[8*1]) | (x5 = blk[8*7]) | (x6 = blk[8*5]) | (x7 = blk[8*3])))
 {
  blk[8*0] = blk[8*1] = blk[8*2] = blk[8*3] =
   blk[8*4] = blk[8*5] = blk[8*6] = blk[8*7] = ((blk[0] + 32) >> 6);
  return 0;
 }

 z13 = x4 + x5;
 z12 = x4 - x5;
 z11 = z13 * 565 + 4;
 z13 = z13 * 1108;
 z12 = z12 * 3546;
 x4 = (z11 + z12) >> 3;
 x5 = (z11 - z12) >> 3;

 z13 = x6 + x7;
 z10 = x6 - x7;
 z11 = z13 * 2408 + 4;
 z13 = z13 * 1609;
 z10 = z10 * 4082;
 x6 = (z11 - z10) >> 3;
 x7 = (z11 - z13) >> 3;

 tmp = x0 * 256 + 8192;
 z11 = x1 + x3;
 z12 = x1 - x3;
 z13 = x2 + x6;
 z10 = x2 - x6;
 x1 = z11 * 1108;
 x2 = z12 * 2841;
 x3 = (z13 * 1773 + 4) >> 3;
 x6 = (z10 * 4520 + 4) >> 3;
 z11 = x4 + x2;
 z12 = x4 - x2;
 z13 = x5 + x3;
 z10 = x5 - x3;
 x3 = tmp + x1;
 tmp -= x1;
 z11 = z11 + x6;
 z12 = z12 - x6;
 z13 = z13 + x7;
 z10 = z10 - x7;
 x7 = tmp + z10;
 tmp -= z10;
 z11 = (z11 + z13) >> 14;
 z13 = (z11 - z13) >> 14;
 blk[0] = (short) ((tmp + z12) >> 14);
 blk[1] = (short) ((tmp - z12) >> 14);
 blk[2] = (short) ((x3 + z11) >> 14);
 blk[3] = (short) ((x3 - z11) >> 14);
 blk[4] = (short) ((x7 + z13) >> 14);
 blk[5] = (short) ((x7 - z13) >> 14);
 blk[6] = (short) ((tmp - z12) >> 14);
 blk[7] = (short) ((tmp + z12) >> 14);

 return 1;
}