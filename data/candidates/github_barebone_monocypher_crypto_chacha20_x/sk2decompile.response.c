unsigned long long crypto_chacha20_x(unsigned char *c, const unsigned char *m,
                                     unsigned int mlen, const unsigned char *k,
                                     const unsigned char *n,
                                     unsigned long long d) {
  unsigned char h[32];
  crypto_chacha20_h(h, k, n);
  d = crypto_chacha20_djb(c, m, mlen, h, n + 16, d);
  crypto_wipe(h, 32);
  return d;
}