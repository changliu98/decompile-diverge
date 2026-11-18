int sios_ecdsa_key_to_pubkey(void *pubkey, void *key)
{
  struct sios_ecdsa_pubkey *p = (struct sios_ecdsa_pubkey *)pubkey;
  struct sios_ecdsa_key *k = (struct sios_ecdsa_key *)key;
  p->point.x = k->point.x ^ 0x8000000000000000UL;
  p->point.y = k->point.y;
  return 1;
}