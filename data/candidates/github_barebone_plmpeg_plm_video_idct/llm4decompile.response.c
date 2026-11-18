void plm_video_idct(int *block)
{
 int i;
 int a0, a1, a2, a3, a4, a5, a6, a7;
 int b0, b1, b2, b3, b4, b5, b6, b7;
 int c0, c1, c2, c3, c4, c5, c6, c7;
 int d0, d1, d2, d3, d4, d5, d6, d7;
 int e0, e1, e2, e3, e4, e5, e6, e7;
 int f0, f1, f2, f3, f4, f5, f6, f7;
 int tmp0, tmp1, tmp2, tmp3;


 for (i = 0; i < 8; i++) {
  a0 = block[8 + i];
  a1 = block[16 + i];
  a2 = block[24 + i];
  a3 = block[32 + i];
  a4 = block[40 + i];
  a5 = block[48 + i];
  a6 = block[56 + i];
  a7 = block[64 + i];

  b0 = a0 + a1;
  b1 = a0 - a1;
  b2 = (a2 * 379 - a6 * 90 + 128) >> 8;
  b3 = (a2 * 90 + a6 * 379 + 128) >> 8;
  b4 = a4 + a5;
  b5 = a4 - a5;
  b6 = (a2 - a6) * 443 + (a4 - a5) * 90 + 128;
  b7 = (a2 + a6) * 443 - (a4 + a5) * 90 + 128;

  c0 = b0 + b4;
  c1 = b1 + b5;
  c2 = b1 - b5;
  c3 = b0 - b4;
  c4 = b3 - b7;
  c5 = b3 + b7;
  c6 = b2 - b6;
  c7 = b2 + b6;

  d0 = c0 + c5;
  d1 = c1 + c6;
  d2 = c2 - c4;
  d3 = c3 - c7;
  d4 = c3 + c7;
  d5 = c2 + c4;
  d6 = c1 - c6;
  d7 = c0 - c5;

  block[0 + i] = d0;
  block[8 + i] = d1;
  block[16 + i] = d2;
  block[24 + i] = d3;
  block[32 + i] = d4;
  block[40 + i] = d5;
  block[48 + i] = d6;
  block[56 + i] = d7;
 }


 for (i = 0; i < 64; i += 8) {
  a0 = block[0 + i];
  a1 = block[1 + i];
  a2 = block[2 + i];
  a3 = block[3 + i];
  a4 = block[4 + i];
  a5 = block[5 + i];
  a6 = block[6 + i];
  a7 = block[7 + i];

  b0 = a0 + a1;
  b1 = a0 - a1;
  b2 = (a2 * 379 - a6 * 90 + 128) >> 8;
  b3 = (a2 * 90 + a6 * 379 + 128) >> 8;
  b4 = a4 + a5;
  b5 = a4 - a5;
  b6 = (a2 - a6) * 443 + (a4 - a5) * 90 + 128;
  b7 = (a2 + a6) * 443 - (a4 + a5) * 90 + 128;

  c0 = b0 + b4;
  c1 = b1 + b5;
  c2 = b1 - b5;
  c3 = b0 - b4;
  c4 = b3 - b7;
  c5 = b3 + b7;
  c6 = b2 - b6;
  c7 = b2 + b6;

  d0 = c0 + c5;
  d1 = c1 + c6;
  d2 = c2 - c4;
  d3 = c3 - c7;
  d4 = c3 + c7;
  d5 = c2 + c4;
  d6 = c1 - c6;
  d7 = c0 - c5;

  block[0 + i] = (d0 + 128) >> 8;
  block[1 + i] = (d1 + 128) >> 8;
  block[2 + i] = (d2 + 128) >> 8;
  block[3 + i] = (d3 + 128) >> 8;
  block[4 + i] = (d4 + 128) >> 8;
  block[5 + i] = (d5 + 128) >> 8;
  block[6 + i] = (d6 + 128) >> 8;
  block[7 + i] = (d7 + 128) >> 8;
 }
}