void crypto_chacha20_h(unsigned char *out, const unsigned char *in,
                       const unsigned char *k) {
  unsigned int x[16];
  unsigned char *out_ptr = out;
  const unsigned char *in_ptr = in;
  const unsigned char *k_ptr = k;
  load32_le_buf(x, chacha_const, 4);
  load32_le_buf(x + 4, in_ptr, 8);
  load32_le_buf(x + 12, k_ptr, 4);
  chacha20_rounds(x, x);
  store32_le_buf(out_ptr, x, 4);
  store32_le_buf(out_ptr + 16, x + 12, 4);
  crypto_wipe((unsigned char *)x, sizeof(x));
}