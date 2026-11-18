int aes_decrypt_cbc(unsigned char *in, int inlen, unsigned char *out,
                    unsigned char *key, int keysize, unsigned char *iv) {
  int n, nblocks;
  unsigned char prev[16], block[16], tmp[16];
  if (inlen % 16) return 0;
  nblocks = inlen / 16;
  memcpy(prev, iv, 16);
  for (n = 0; n < nblocks; n++) {
    memcpy(block, in + n * 16, 16);
    aes_decrypt(block, tmp, key, keysize);
    xor_buf(prev, tmp, 16);
    memcpy(out + n * 16, tmp, 16);
    memcpy(prev, block, 16);
  }
  return 1;
}