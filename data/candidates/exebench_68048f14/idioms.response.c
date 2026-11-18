void vinv(struct f25519_t *r)
{
  ((long *) r->x)[0] ^= 0x8000000000000000UL;
  ((long *) r->x)[1] ^= 0x8000000000000000UL;
  ((long *) r->x)[2] ^= 0x8000000000000000UL;
}