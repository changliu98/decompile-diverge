static unsigned int par_msquares_argb(unsigned char *pixel, int bpp) {
  int i;
  unsigned int argb = 0;
  if (bpp == 4) {
    argb = pixel[0] << 16 | pixel[1] << 8 | pixel[2] << 0 | pixel[3] << 24;
  } else {
    for (i = 0; i < bpp; i++) {
      argb = (argb << 8) | pixel[i];
    }
  }
  return argb;
}