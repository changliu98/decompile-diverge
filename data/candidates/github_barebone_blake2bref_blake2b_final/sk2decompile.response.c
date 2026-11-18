int blake2b_final(blake2b_state *S, unsigned char *out, unsigned int outlen) {
  unsigned char buf[64];
  size_t i;
  memset(buf, 0, 64);
  if (out == NULL || outlen < S->outlen) return -1;
  if (blake2b_is_lastblock(S)) return -1;
  blake2b_increment_counter(S, S->buflen);
  blake2b_set_lastblock(S);
  memset(S->buf + S->buflen, 0, 128 - S->buflen);
  blake2b_compress(S, S->buf);
  for (i = 0; i < 8; i++) store64(buf + 8 * i, S->h[i]);
  memcpy(out, buf, S->outlen);
  secure_zero_memory(buf, 64);
  return 0;
}