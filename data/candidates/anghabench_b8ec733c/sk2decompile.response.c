static void vc1_inv_trans_8x8_c(unsigned char *block) {
  int i;
  int a, b, c, d, e, f, g, h;
  int *src = (int *)block;
  int *dst = (int *)block;
  int tmp[64];
  int *dst2 = tmp;
  for (i = 0; i < 8; i++) {
    a = src[0] + src[32];
    b = src[0] - src[32];
    c = src[16] * 16 + src[48] * 6;
    d = src[48] * 6 - src[16] * 16;
    e = a * 12 + 4;
    f = b * 12 + 4;
    g = e + c;
    h = f + d;
    e = e - c;
    f = f - d;
    a = src[8] * 16 + src[24] * 15 + src[40] * 9 + src[56] * 4;
    b = src[8] * 15 - src[24] * 4 - src[40] * 16 - src[56] * 9;
    c = src[56] * 15 + src[40] * 4 + src[8] * 9 - src[24] * 16;
    d = src[40] * 15 + src[8] * 4 - src[24] * 9 - src[56] * 16;
    dst2[0] = (a + g) >> 3;
    dst2[1] = (b + h) >> 3;
    dst2[2] = (c + e) >> 3;
    dst2[3] = (d + f) >> 3;
    dst2[4] = (f - d) >> 3;
    dst2[5] = (e - c) >> 3;
    dst2[6] = (h - b) >> 3;
    dst2[7] = (g - a) >> 3;
    src++;
    dst2 += 8;
  }
  src = tmp;
  dst2 = dst;
  for (i = 0; i < 8; i++) {
    a = src[0] + src[32];
    b = src[0] - src[32];
    c = src[16] * 16 + src[48] * 6;
    d = src[48] * 6 - src[16] * 16;
    e = a * 12 + 64;
    f = b * 12 + 64;
    g = e + c;
    h = f + d;
    e = e - c;
    f = f - d;
    a = src[8] * 16 + src[24] * 15 + src[40] * 9 + src[56] * 4;
    b = src[8] * 15 - src[24] * 4 - src[40] * 16 - src[56] * 9;
    c = src[56] * 15 + src[40] * 4 + src[8] * 9 - src[24] * 16;
    d = src[40] * 15 + src[8] * 4 - src[24] * 9 - src[56] * 16;
    dst2[0] = (a + g) >> 7;
    dst2[8] = (b + h) >> 7;
    dst2[16] = (c + e) >> 7;
    dst2[24] = (d + f) >> 7;
    dst2[32] = (f - d + 1) >> 7;
    dst2[40] = (e - c + 1) >> 7;
    dst2[48] = (h - b + 1) >> 7;
    dst2[56] = (g - a + 1) >> 7;
    src++;
    dst2++;
  }
}