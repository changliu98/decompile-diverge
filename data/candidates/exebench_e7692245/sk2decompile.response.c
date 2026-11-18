void dwordstore(unsigned char *a, unsigned int b) {
  a[0] = b;
  a[1] = b >> 8;
  a[2] = b >> 16;
  a[3] = b >> 24;
}