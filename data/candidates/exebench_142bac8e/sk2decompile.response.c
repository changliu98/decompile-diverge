void wordstore(unsigned char *p, int i) {
  unsigned short *pw;
  pw = (unsigned short *)p;
  *pw = i;
}