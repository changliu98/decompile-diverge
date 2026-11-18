static void idct_row(short *blk)
{
 int x0, x1, x2, x3, x4, x5, x6, x7, x8;

 x0 = W0 * blk[0] + W0 * blk[4];
 x1 = W1 * blk[1] + W7 * blk[7];
 x2 = W2 * blk[2] + W6 * blk[6];
 x3 = W3 * blk[3] - W5 * blk[5];
 x4 = W0 * blk[0] - W0 * blk[4];
 x5 = W5 * blk[5] + W3 * blk[3];
 x6 = W6 * blk[2] - W2 * blk[6];
 x7 = W7 * blk[1] - W1 * blk[7];

 x8 = ((x1 - x5 + x7 - x3) * 181 + 128) >> 8;
 x1 = ((x1 - x5 - x7 + x3) * 181 + 128) >> 8;

 blk[0] = (x0 + x2 + x1 + x5 + 128) >> 8;
 blk[1] = (x4 + x6 + x8 + 128) >> 8;
 blk[2] = (x4 - x6 + x1 + 128) >> 8;
 blk[3] = (x0 - x2 + x7 + x3 + 128) >> 8;
 blk[4] = (x0 - x2 - x7 - x3 + 128) >> 8;
 blk[5] = (x4 - x6 - x1 + 128) >> 8;
 blk[6] = (x4 + x6 - x8 + 128) >> 8;
 blk[7] = (x0 + x2 - x1 - x5 + 128) >> 8;
}