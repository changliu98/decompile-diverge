static unsigned char *dlfb_dummy_render(unsigned char *p) {
  p[0] = 0xa1;
  p[1] = 0x6a;
  p[2] = 0x00;
  p[3] = 0x00;
  p[4] = 0x00;
  p[5] = 0x01;
  p[6] = 0x00;
  p[7] = 0x00;
  p[8] = 0x00;
  p += 9;
  return p;
}