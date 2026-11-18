int blake2b_init(blake2b_state *S, unsigned int outlen) {
  blake2b_param P;
  if (outlen == 0 || outlen > 64) return -1;
  P.digest_length = outlen;
  P.key_length = 0;
  P.fanout = 1;
  P.depth = 1;
  store32(&P.leaf_length, 0);
  store32(&P.node_offset, 0);
  store32(&P.xof_length, 0);
  P.node_depth = 0;
  P.inner_length = 0;
  memset(P.reserved, 0, 8);
  memset(P.salt, 0, 16);
  memset(P.personal, 0, 8);
  return blake2b_init_param(S, &P);
}