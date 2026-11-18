static unsigned long chacha20(unsigned char *cipher_text, unsigned char *plain_text, unsigned long text_size, unsigned char *key, unsigned char *nonce, unsigned long ctr)
{
  unsigned char sub_key[32];
  crypto_chacha20_h(sub_key, key, nonce);
  ctr = crypto_chacha20_djb(cipher_text, plain_text, text_size, sub_key, nonce + 16, ctr);
  crypto_wipe(sub_key, sizeof sub_key);
  return ctr;
}