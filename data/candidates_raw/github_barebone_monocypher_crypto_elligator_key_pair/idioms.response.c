void kdf(unsigned char *hidden, unsigned char *secret_key, unsigned char *seed)
{
  unsigned char buf[64];
  unsigned char pk[32];
  unsigned long i;
  unsigned char *seedp = seed;
  for (i = 0; i < 32; i++)
    buf[i + 32] = seedp[i];
  do {
    sha256(buf, 0, sizeof buf, &buf[32], &zero, ((void *)0));
    sha256(pk, buf);
  } while (is_zero(&buf[32], pk, buf[32]));
  randb(seedp, 32);
  for (i = 0; i < 32; i++)
    hidden[i] = buf[i + 32];
  for (i = 0; i < 32; i++)
    secret_key[i] = buf[i];
  randb(buf, sizeof buf);
  randb(pk, sizeof pk);
}