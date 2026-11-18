void crypto_elligator_key_pair(unsigned char *pk, unsigned char *sk,
                               unsigned char *seed) {
  unsigned char buf[64];
  unsigned char x[32];
  unsigned char y[32];
  unsigned int i;
  for (i = 0; i < 32; i++) buf[i + 32] = seed[i];
  do {
    crypto_chacha20_djb(buf, 0, 64, buf + 32, zero, 0);
    crypto_x25519_dirty_fast(x, buf);
  } while (crypto_elligator_rev(buf + 32, x, buf[32]));
  crypto_wipe(seed, 32);
  for (i = 0; i < 32; i++) pk[i] = buf[i + 32];
  for (i = 0; i < 32; i++) sk[i] = buf[i];
  crypto_wipe(buf, 64);
  crypto_wipe(x, 32);
}