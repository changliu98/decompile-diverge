int blake2b_init(void *ctx, unsigned long outlen)
{
  struct blake2b_param p;
  struct blake2b_state *state = (blake2b_state *)ctx;
  if (state == ((void *)0)) return -1;
  if (outlen == 0 || outlen > 64) {
    blake2b_invalidate_state(state);
    return -1;
  }
  p.digest_length = (unsigned long)outlen;
  p.key_length = 0;
  p.fanout = 1;
  p.depth = 1;
  p.leaf_length = 0;
  p.node_offset = 0;
  p.node_depth = 0;
  p.inner_length = 0;
  memset(p.reserved, 0, sizeof p.reserved);
  memset(p.salt, 0, sizeof p.salt);
  memset(p.personal, 0, sizeof p.personal);
  return blake2b_init_param(state, &p);
}