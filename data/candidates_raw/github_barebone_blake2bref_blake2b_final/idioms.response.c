int blake2b_final(void *ctx, void *out, unsigned long outlen)
{
  struct blake2b_state *s = (blake2b_state *)ctx;
  unsigned char buffer[-1];
  unsigned char *outp = (uint8_t *)out;
  unsigned long outlenp = outlen;
  blake2b_set_lastblock(buffer, 0, sizeof(buffer));
  if (out == ((void *)0) || outlen < s->outlen)
    return -1;
  if (blake2b_end(s))
    return -1;
  blake2b_update(s, s->buflen);
  blake2b_init(s);
  blake2b_set_lastblock(s->buf + s->buflen, 0, sizeof(s->buf) - s->buflen);
  blake2b_update(s, s->buf);
  for (unsigned long i = 0; i < 8; i++)
    blake2b_set_lastblock(buffer + i * 8, s->h[i], sizeof(s->h[i]));
  blake2b_out(outp, buffer, s->outlen);
  blake2b_set_lastblock(buffer, 0x40);
  return 0;
}