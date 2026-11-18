static void stbi__idct_block(unsigned char *image, int stride, short *data) {
  int temp[64];
  int *t = temp;
  short *d = data;
  int i;
  for (i = 0; i < 8; i++, d++, t++) {
    if (d[8] == 0 && d[16] == 0 && d[24] == 0 && d[32] == 0 && d[40] == 0 &&
        d[48] == 0 && d[56] == 0) {
      int a = d[0] << 2;
      t[56] = a;
      t[48] = a;
      t[40] = a;
      t[32] = a;
      t[24] = a;
      t[16] = a;
      t[8] = a;
      t[0] = a;
    } else {
      int a0, a1, a2, a3, a4, a5, a6, a7;
      int b0, b1, b2, b3;
      b0 = d[16];
      b1 = d[48];
      b2 = (2217 * (b0 + b1)) - (7567 * b1);
      b3 = (2217 * (b0 + b1)) + (3135 * b0);
      a0 = d[0];
      a1 = d[32];
      a2 = (a0 + a1) << 12;
      a3 = a2 + b3;
      a4 = a2 - b3;
      a5 = a0 - a1;
      a6 = (a5 << 12);
      a7 = a6 + b2;
      b0 = a6 - b2;
      b1 = d[56];
      b2 = d[40];
      b3 = d[24];
      a1 = d[8];
      a0 = (b1 + b2 + b3 + a1);
      a2 = (4816 * a0);
      a3 = a2 - (3685 * (a1 + b1));
      a4 = a2 - (10497 * (b2 + b3));
      a5 = a2 - (8034 * (b1 + b3));
      a6 = a2 - (1597 * (b2 + a1));
      a7 = a3 + (6149 * a1);
      b0 = a4 + (12586 * b3);
      b1 = a5 + a6;
      b2 = a4 + a6;
      b3 = a3 + a6;
      a2 += 512;
      a3 += 512;
      a4 += 512;
      a5 += 512;
      t[0] = (a2 + a7) >> 10;
      t[56] = (a2 - a7) >> 10;
      t[8] = (a3 + b0) >> 10;
      t[48] = (a3 - b0) >> 10;
      t[16] = (a4 + b1) >> 10;
      t[40] = (a4 - b1) >> 10;
      t[24] = (a5 + b2) >> 10;
      t[32] = (a5 - b2) >> 10;
    }
  }
  for (i = 0, t = temp, image = image; i < 8; i++, t += 8, image += stride) {
    int a0, a1, a2, a3, a4, a5, a6, a7;
    int b0, b1, b2, b3;
    b0 = t[2];
    b1 = t[6];
    b2 = (2217 * (b0 + b1)) - (7567 * b1);
    b3 = (2217 * (b0 + b1)) + (3135 * b0);
    a0 = t[0];
    a1 = t[4];
    a2 = (a0 + a1) << 12;
    a3 = a2 + b3;
    a4 = a2 - b3;
    a5 = a0 - a1;
    a6 = (a5 << 12);
    a7 = a6 + b2;
    b0 = a6 - b2;
    b1 = t[7];
    b2 = t[5];
    b3 = t[3];
    a1 = t[1];
    a0 = (b1 + b2 + b3 + a1);
    a2 = (4816 * a0);
    a3 = a2 - (3685 * (a1 + b1));
    a4 = a2 - (10497 * (b2 + b3));
    a5 = a2 - (8034 * (b1 + b3));
    a6 = a2 - (1597 * (b2 + a1));
    a7 = a3 + (6149 * a1);
    b0 = a4 + (12586 * b3);
    b1 = a5 + a6;
    b2 = a4 + a6;
    b3 = a3 + a6;
    a2 += 16842752;
    a3 += 16842752;
    a4 += 16842752;
    a5 += 16842752;
    image[0] = stbi__clamp((a2 + a7) >> 17);
    image[7] = stbi__clamp((a2 - a7) >> 17);
    image[1] = stbi__clamp((a3 + b0) >> 17);
    image[6] = stbi__clamp((a3 - b0) >> 17);
    image[2] = stbi__clamp((a4 + b1) >> 17);
    image[5] = stbi__clamp((a4 - b1) >> 17);
    image[3] = stbi__clamp((a5 + b2) >> 17);
    image[4] = stbi__clamp((a5 - b2) >> 17);
  }
}