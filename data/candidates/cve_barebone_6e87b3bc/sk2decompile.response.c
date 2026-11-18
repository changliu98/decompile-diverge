void quicktake_100_load_raw(void) {
  unsigned char c = 0;
  int x, y;
  int img[484][644];
  getbithuff(-1, 0);
  memset(img, 128, sizeof(img));
  for (y = 2; y < height + 2; y++) {
    for (x = y & 1 ? 3 : 2; x < width + 2; x += 2) {
      int v = (img[y - 1][x - 1] + 2 * img[y - 1][x + 1] + img[y - 1][x + 642]) >>
              2;
      v += quicktake_100_dither[getbithuff(4, 0)];
      c = (v < 0 ? 0 : (v > 255 ? 255 : v));
      img[y][x] = c;
      if (x < 4) {
        img[y + 1][(y & 1) ? 0 : 1] = c;
        img[y - 1][x + 642] = c;
      }
      if (y == 2) {
        img[1][x + 3] = c;
        img[1][x + 1] = c;
      }
    }
    img[y][x] = c;
  }
  for (int pass = 0; pass < 2; pass++) {
    for (y = pass + 2; y < height + 2; y += 2) {
      for (x = 3 - (y & 1); x < width + 2; x += 2) {
        int d;
        if (y < 4 || x < 4)
          d = 2;
        else
          d = (abs32(img[y - 1][x + 642] - img[y - 2][x - 2]) +
               abs32(img[y - 2][x] - img[y - 2][x - 2]) +
               abs32(img[y - 2][x] - img[y - 1][x + 642]));
        d = (d < 4 ? 0 : (d < 8 ? 1 : (d < 16 ? 2 : (d < 32 ? 3
                                                            : (d < 48 ? 4
                                                                      : 5)))));
        int v = (img[y - 1][x + 642] + img[y - 2][x]) >> 1;
        v += quicktake_100_quant[d * 4 + getbithuff(2, 0)];
        c = (v < 0 ? 0 : (v > 255 ? 255 : v));
        img[y][x] = c;
        if (y < 4) img[y - 2][x + 2] = c;
        if (x < 4) img[y + 1][x + 642] = c;
      }
    }
  }
  for (y = 2; y < height + 2; y++) {
    for (x = 3 - (y & 1); x < width + 2; x += 2) {
      int v = (img[y][x] + 4 * img[y][x + 1] + img[y - 1][x + 643]) >> 1;
      v -= 256;
      c = (v < 0 ? 0 : (v > 255 ? 255 : v));
      img[y][x] = c;
    }
  }
  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {
      image[y * bytesperline + x] = quicktake_100_pal[img[y + 2][x + 2]];
    }
  }
  maxval = 1023;
}