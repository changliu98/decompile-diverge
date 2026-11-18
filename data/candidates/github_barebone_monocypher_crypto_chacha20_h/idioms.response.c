void crypto_chacha20_h(unsigned char *out, unsigned char *key, unsigned char *in)
{
  unsigned char *outp = out;
  unsigned char *keyp = key;
  unsigned char *inp = in;
  unsigned int block[16];
  load32_le_buf(block, chacha20_constant, sizeof(chacha20_constant));
  load32_le_buf(block + 4, keyp, sizeof(unsigned long long));
  load32_le_buf(block + 12, inp, sizeof(unsigned long long));
  chacha20_rounds(block, block);
  store32_le_buf(outp, block, sizeof(unsigned long long));
  store32_le_buf(outp + sizeof(unsigned long long), block + 12, sizeof(unsigned long long));
  crypto_wipe(block, sizeof(block));
}