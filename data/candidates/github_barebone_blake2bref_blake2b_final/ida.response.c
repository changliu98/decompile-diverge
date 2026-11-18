int __cdecl blake2b_final(blake2b_state *S, void *out, size_t outlen)
{
  size_t i; // [rsp+8h] [rbp-68h]
  uint8_t buffer[64]; // [rsp+10h] [rbp-60h] BYREF
  size_t outlena; // [rsp+50h] [rbp-20h]
  void *outa; // [rsp+58h] [rbp-18h]
  blake2b_state *Sa; // [rsp+60h] [rbp-10h]

  Sa = S;
  outa = out;
  outlena = outlen;
  memset(buffer, 0, sizeof(buffer));
  if ( !out || outlena < Sa->outlen )
    return -1;
  if ( blake2b_is_lastblock(Sa) )
    return -1;
  blake2b_increment_counter(Sa, Sa->buflen);
  blake2b_set_lastblock(Sa);
  memset(&Sa->buf[Sa->buflen], 0, 128 - Sa->buflen);
  blake2b_compress(Sa, Sa->buf);
  for ( i = 0LL; i < 8; ++i )
    store64(&buffer[8 * i], Sa->h[i]);
  memcpy(outa, buffer, Sa->outlen);
  secure_zero_memory(buffer, 0x40uLL);
  return 0;
}