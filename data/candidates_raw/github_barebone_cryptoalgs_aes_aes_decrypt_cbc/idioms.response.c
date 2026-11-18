int aes_cbc_decrypt(unsigned char *in, unsigned long in_len, unsigned char *out, unsigned char *key, int keysize, unsigned char *iv)
{
  unsigned char buf_in[-1];
  unsigned char buf_out[-1];
  unsigned char iv_buf[-1];
  int i; int blocks;
  if (in_len % 16 != 0)
    return 0;
  blocks = in_len / 16;
  memcpy(iv_buf, iv, 16);
  for (i = 0; i < blocks; i++) {
    memcpy(buf_in, in + i * 16, 16);
    aes_decrypt(buf_in, buf_out, key, keysize);
    xor_buf(iv_buf, buf_out, 16);
    memcpy(out + i * 16, buf_out, 16);
    memcpy(iv_buf, buf_in, 16);
  }
  return 1;
}