void stbi__idct_block(unsigned char *out, int out_stride, short *in)
{
  int i;
  int *inptr = (int *)in;
  int *outptr = (int *)out;
  int *inptr1 = inptr;
  int *outptr1 = outptr;
  int inbuf[64];
  int *inptr2 = inbuf;
  for (i = 0; i < 8; i++)
  {
    if (inptr1[8] != 0 || inptr1[16] != 0 || inptr1[24] != 0 || inptr1[32] != 0 ||
        inptr1[40] != 0 || inptr1[48] != 0 || inptr1[56] != 0)
    {
      int p2 = inptr1[16];
      int p3 = inptr1[48];
      int t2 = -7567 * p3 + 2217 * (p2 + p3);
      int t3 = 3135 * p2 + 2217 * (p2 + p3);
      int p2a = inptr1[0];
      int p3a = inptr1[32];
      int x0 = t3 + (p2a + p3a) * (1 << 12);
      int x3 = (p2a + p3a) * (1 << 12) - t3;
      int x1 = t2 + (p2a - p3a) * (1 << 12);
      int x2 = (p2a - p3a) * (1 << 12) - t2;
      int t0 = inptr1[56];
      int t1 = inptr1[40];
      int t2a = inptr1[24];
      int t3a = inptr1[8];
      int p5 = p2a + p3a + t1 + t0 + t2a + t3a * (1 << 12);
      int p1 = p5 - 3685 * t3a - 10497 * t2a - 1597 * t1;
      int p2b = p5 - 8034 * t2a - 10497 * t1 - 1223 * t0;
      int p3b = p5 - 8034 * t2a - 1223 * t0;
      int p4 = p5 - 3685 * t3a - 1597 * t1;
      int t3b = t3a * 6149 + p4 + p1;
      int t2b = t2a * 12586 + p3b + p2b;
      int t1a = t1 * 8410 + p4 + p2b;
      int t0a = t0 * 1223 + p3b + p1;
      x0 += (1 << 9);
      x1 += (1 << 9);
      x2 += (1 << 9);
      x3 += (1 << 9);
      inptr2[0] = (t3b + x0) >> 10;
      inptr2[56] = (x0 - t3b) >> 10;
      inptr2[1] = (t2b + x1) >> 10;
      inptr2[48] = (x1 - t2b) >> 10;
      inptr2[2] = (t1a + x2) >> 10;
      inptr2[40] = (x2 - t1a) >> 10;
      inptr2[3] = (t0a + x3) >> 10;
      inptr2[32] = (x3 - t0a) >> 10;
    }
    else
    {
      int v = inptr1[0] * 4;
      inptr2[0] = inptr2[1] = inptr2[2] = inptr2[3] = inptr2[4] = inptr2[5] = inptr