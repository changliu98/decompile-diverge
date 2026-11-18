int shaInit(struct sha_hash *hash)
{
  hash->state[0] = 0x6a09e667;
  hash->state[1] = 0xbb67ae85;
  hash->state[2] = 0x3c6ef372;
  hash->state[3] = 0xa54ff53a;
  hash->state[4] = 0x510e527f;
  return 0;
}