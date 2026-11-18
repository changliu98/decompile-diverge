
static void
poly1305_add(unsigned char h[17], const unsigned char c[17]) {
 unsigned short u;
 unsigned int i;
 for (u = 0, i = 0; i < 17; i++) {
  u += (unsigned short)h[i] + (unsigned short)c[i];
  h[i] = (unsigned char)u & 0xff;
  u >>= 8;
 }
}
