int genx(unsigned char *x, unsigned char *y) {
  int i;
  short xy[256];
  int flag;
  unsigned char *xp;
  unsigned char *yp;
  xp = x;
  yp = y;
  flag = 0;
  for (i = 0; i < 256; i++) xy[i] = -1;
  for (i = 0; i < 256; i++) {
    if (xy[yp[i]] == -1)
      xy[yp[i]] = i;
    else
      flag = 1;
  }
  for (i = 0; i < 256; i++) xp[i] = xy[i];
  if (flag) return -1;
  return 0;
}