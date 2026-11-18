void crypto_eddsa_sign(unsigned char *sig, const unsigned char *sk,
                       const unsigned char *m, unsigned int mlen) {
  unsigned char h[64];
  unsigned char r[32];
  unsigned char s[32];
  unsigned char hs[32];
  unsigned int i;
  crypto_blake2b(h, sizeof h, sk, 32);
  crypto_eddsa_trim_scalar(h, h);
  hash_reduce(s, h + 32, 32, m, mlen, NULL, 0);
  crypto_eddsa_scalarbase(r, s);
  hash_reduce(hs, r, 32, sk + 32, 32, m, mlen);
  for (i = 0; i < 32; i++) sig[i] = r[i];
  crypto_eddsa_mul_add(sig + 32, hs, h, s);
  crypto_wipe(h, sizeof h);
  crypto_wipe(s, sizeof s);
}