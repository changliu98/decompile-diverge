void subpixels(unsigned long pixel, unsigned long *r, unsigned long *g,
               unsigned long *b, unsigned long *a) {
  *r = (pixel >> 24) & 0xff;
  *g = (pixel >> 16) & 0xff;
  *b = (pixel >> 8) & 0xff;
  *a = pixel & 0xff;
}