unsigned long crypto_chacha20_djb(unsigned char *cipher_text, unsigned char *plain_text, unsigned long text_size, unsigned char *key, unsigned char *nonce, unsigned long ctr)
{
  unsigned int pool[16];
  unsigned int input[16];
  unsigned long i; unsigned long j;
  unsigned char *in = (uint8_t *) plain_text;
  unsigned char *out = (uint8_t *) cipher_text;
  load32_le_buf(input, chacha20_constant, sizeof chacha20_constant);
  load32_le_buf(&input[4], key, 8);
  load32_le_buf(&input[14], nonce, 2);
  input[12] = (unsigned int) ctr;
  for (i = 0; i < (text_size / 64); i++)
  {
    chacha20_rounds(pool, input);
    if (in)
    {
      for (j = 0; j < 16; j++)
      {
        unsigned int tmp = input[j] + pool[j];
        unsigned char *in_ = in;
        store32_le(out = out, load32_le(in_) ^ tmp);
        in += 4;
        out += 4;
      }
    }
    else
    {
      for (j = 0; j < 16; j++)
      {
        unsigned int tmp = input[j] + pool[j];
        store32_le(out = out, tmp);
        out += 4;
      }
    }
    if (++input[12] == 0)
      input[13]++;
  }
  text_size &= (64 - 1);
  if (text_size)
  {
    if (!in)
      in = zero;
    chacha20_rounds(pool, input);
    for (j = 0; j < 16; j++)
      store32_le(&pool[j], input[j] + pool[j]);
    for (i = 0; i < text_size; i++)
      out[i] = in[i] ^ pool[i];
    crypto_wipe(pool, sizeof pool);
  }
  ctr = (text_size == 0 ? 0 : 1) + (input[13] << 32) + input[12];
  crypto_wipe(input, sizeof input);
  crypto_wipe(pool, sizeof pool);
  return (ctr);
}