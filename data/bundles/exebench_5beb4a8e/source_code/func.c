
static void
poly1305_squeeze(unsigned char h[17], unsigned long hr[17]) {
 unsigned long u;
 unsigned int i;
 u = 0;
 for (i = 0; i < 16; i++) {
  u += hr[i];
  h[i] = (unsigned char)u & 0xff;
  u >>= 8;
 }
 u += hr[16];
 h[16] = (unsigned char)u & 0x03;
 u >>= 2;
 u += (u << 2);
 for (i = 0; i < 16; i++) {
  u += h[i];
  h[i] = (unsigned char)u & 0xff;
  u >>= 8;
 }
 h[16] += (unsigned char)u;
}
