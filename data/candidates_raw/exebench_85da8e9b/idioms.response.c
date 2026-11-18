void bgr2rgb(unsigned char mask, unsigned short col1, unsigned short col2, unsigned char *rgb)
{
  unsigned short r1; unsigned short g1; unsigned short b1;
  unsigned short r2; unsigned short g2; unsigned short b2;
  r1 = (col1 & 0x1f) * 8;
  g1 = ((col1 >> 3) & 0xfc);
  b1 = ((col1 >> 6) & 0xf8);
  r2 = (col2 & 0x1f) * 8;
  g2 = ((col2 >> 3) & 0xfc);
  b2 = ((col2 >> 6) & 0xf8);
  switch (mask) {
  case 0:
    rgb[0] = r1;
    rgb[1] = g1;
    rgb[2] = b1;
    break;
  case 1:
    rgb[0] = r2;
    rgb[1] = g2;
    rgb[2] = b2;
    break;
  case 2:
    if (col1 > col2) {
      rgb[0] = (r2 + r1 * 2) / 3;
      rgb[1] = (g2 + g1 * 2) / 3;
      rgb[2] = (b2 + b1 * 2) / 3;
    }
    else {
      rgb[0] = (r2 + r1) / 2;
      rgb[1] = (g2 + g1) / 2;
      rgb[2] = (b2 + b1) / 2;
    }
    break;
  case 3:
    if (col1 > col2) {
      rgb[0] = (r2 * 2 + r1) / 3;
      rgb[1] = (g2 * 2 + g1) / 3;
      rgb[2] = (b2 * 2 + b1) / 3;
    }
    else {
      rgb[0] = 0;
      rgb[1] = 0;
      rgb[2] = 0;
    }
    break;
  }
}