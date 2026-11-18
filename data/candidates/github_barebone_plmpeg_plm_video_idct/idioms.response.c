void plm_video_idct(int *block)
{
  int i; int j;
  int b1; int b2; int b3; int b4; int b5; int b6;
  int tmp1; int tmp2;
  int x0; int x1; int x2; int x3; int x4;
  int y0; int y1; int y2; int y3; int y4; int y5; int y6; int y7;
  for (i = 0; i < 8; i++) {
    b1 = block[i * 8 + 0];
    b3 = block[i * 8 + 2] + block[i * 8 + 12];
    b4 = block[i * 8 + 4] - block[i * 8 + 20];
    tmp1 = block[i * 8 + 16] + block[i * 8 + 8];
    tmp2 = block[i * 8 + 4] + block[i * 8 + 20];
    b6 = block[i * 8 + 8] - block[i * 8 + 16];
    b2 = block[i * 8 + 1];
    x4 = ((b6 * 473 - b4 * 196 + 128) >> 8) - (tmp1 + tmp2);
    x0 = x4 - ((tmp1 - tmp2) * 362 + 128) >> 8;
    x2 = ((block[i * 8 + 12] - block[i * 8 + 2]) * 362 + 128) >> 8
      - b3;
    y3 = b2 + x2 - b1;
    y4 = b1 + b2 + b3;
    y5 = b2 - x2 - b1;
    y6 = b1 + b2 - b3;
    y7 = ((tmp1 - tmp2) * 362 + 128) >> 8 - x4
      - ((b4 * 196 + b6 * 473 + 128) >> 8);
    block[i * 8 + 0] = (y4 + tmp1 + tmp2 + 128) >> 8;
    block[i * 8 + 1] = (y3 + x4 + 128) >> 8;
    block[i * 8 + 2] = (y5 - x0 + 128) >> 8;
    block[i * 8 + 3] = (y6 - y7 + 128) >> 8;
    block[i * 8 + 4] = (y7 + y6 + 128) >> 8;
    block[i * 8 + 5] = (y5 + x0 + 128) >> 8;
    block[i * 8 + 6] = (y3 - x4 + 128) >> 8;
    block[i * 8 + 7] = (y4 - (tmp1 + tmp2) + 128) >> 8;
  }
  for (i = 0; i < 64; i += 8) {
    b1 = block[i + 4];
    b3 = block[i + 6] + block[i + 2];
    b4 = block[i + 5] - block[i + 3];
    tmp1 = block[i + 7] + block[i + 1];
    tmp2 = block[i + 5] + block[i + 3];
    b6 = block[i + 1] - block[i + 7];
    b2 = block[i + 0];
    x4 = ((b6 * 473 - b4 * 196 + 128) >> 8) - (tmp1 + tmp2);
    x0 = x4 - ((tmp1 - tmp2) * 362 + 128) >> 8;
    x2 = ((block[i + 2] - block[i + 6]) * 362 + 128) >> 8 - b3;
    y3 = b2 + x2 - b1;
    y4 = b1 + b2 + b3;
    y5 = b2 - x2 - b1;
    y6 = b1 + b2 - b3;
    y7 = ((tmp1 - tmp2) * 362 + 128) >> 8 - x4
      - ((b4 * 196 + b6 * 473 + 128) >> 8);
    block[i + 0] = (y4 + tmp1 + tmp2 + 128) >> 8;
    block[i + 1] = (y3 + x4 + 128) >> 8;
    block[i + 2] = (y5 - x0 + 128) >> 8;
    block[i + 3] = (y6 - y7 + 128) >> 8;
    block[i + 4] = (y7 + y6 + 128) >> 8;
    block[i + 5] = (y5 + x0 + 128) >> 8;
    block[i + 6] = (y3 - x4 + 128) >> 8;
    block[i + 7] = (y4 - (tmp1 + tmp2) + 128) >> 8;
  }
  return;
}