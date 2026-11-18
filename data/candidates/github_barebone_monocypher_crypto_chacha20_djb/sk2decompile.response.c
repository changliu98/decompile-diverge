unsigned long long crypto_chacha20_djb(unsigned char *c, const unsigned char *m,
                                       unsigned long long mlen,
                                       const unsigned char *n,
                                       const unsigned char *k,
                                       unsigned long long ic) {
  unsigned int x[16];
  unsigned int s[16];
  unsigned int t[16];
  unsigned int i;
  unsigned int j;
  unsigned long long blocks;
  load32_le_buf(s, chacha_const, 4);
  load32_le_buf(s + 4, n, 8);
  load32_le_buf(s + 14, k, 2);
  s[12] = (unsigned int)ic;
  s[13] = (unsigned int)(ic >> 32);
  blocks = mlen >> 6;
  for (i = 0; i < blocks; i++) {
    chacha20_rounds(t, s);
    if (m) {
      for (j = 0; j < 16; j++) {
        unsigned int u = s[j] + t[j];
        store32_le(c, u ^ load32_le(m));
        c += 4;
        m += 4;
      }
    } else {
      for (j = 0; j < 16; j++) {
        unsigned int u = s[j] + t[j];
        store32_le(c, u);
        c += 4;
      }
    }
    s[12]++;
    if (s[12] == 0) s[13]++;
  }
  mlen &= 63;
  if (mlen) {
    if (!m) m = zero;
    chacha20_rounds(t, s);
    for (j = 0; j < 16; j++) {
      unsigned int u = s[j] + t[j];
      store32_le(x, u);
      x += 4;
    }
    for (j = 0; j < mlen; j++) c[j] = m[j] ^ x[j];
    crypto_wipe(x, 64);
  }
  ic = s[12] + (((unsigned long long)s[13]) << 32);
  ic += (mlen != 0);
  crypto_wipe(t, 64);
  crypto_wipe(s, 64);
  return ic;
}