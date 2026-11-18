void unpack_dxt(unsigned char code, unsigned short c0, unsigned short c1,
                unsigned char *rgb) {
  unsigned short r0, g0, r1, g1;
  r0 = (c0 & 0x1f) * 8;
  g0 = ((c0 >> 3) & 0xfc);
  r1 = (c1 & 0x1f) * 8;
  g1 = ((c1 >> 3) & 0xfc);
  switch (code) {
    case 0:
      rgb[0] = r0;
      rgb[1] = g0;
      rgb[2] = (c0 >> 8) & 0xf8;
      break;
    case 1:
      rgb[0] = r1;
      rgb[1] = g1;
      rgb[2] = (c1 >> 8) & 0xf8;
      break;
    case 2:
      if (c0 > c1) {
        rgb[0] = (2 * r0 + r1) / 3;
        rgb[1] = (2 * g0 + g1) / 3;
        rgb[2] = (2 * ((c0 >> 8) & 0xf8) + ((c1 >> 8) & 0xf8)) / 3;
      } else {
        rgb[0] = (r0 + r1) / 2;
        rgb[1] = (g0 + g1) / 2;
        rgb[2] = ((c0 >> 8) & 0xf8 + (c1 >> 8) & 0xf8) / 2;
      }
      break;
    case 3:
      if (c0 > c1) {
        rgb[0] = (r0 + 2 * r1) / 3;
        rgb[1] = (g0 + 2 * g1) / 3;
        rgb[2] = ((c0 >> 8) & 0xf8 + 2 * ((c1 >> 8) & 0xf8)) / 3;
      } else {
        rgb[0] = rgb[1] = rgb[2] = 0;
      }
      break;
  }
}