int blake2b_final( blake2b_state *S, uint8_t *out, size_t outlen )
{
  uint8_t buffer[64];
  size_t i;

  memset( buffer, 0, 64 );

  if( !out || outlen < S->outlen )
    return -1;

  if( blake2b_is_lastblock( S ) )
    return -1;

  blake2b_increment_counter( S, S->buflen );
  blake2b_set_lastblock( S );
  memset( S->buf + S->buflen, 0, 128 - S->buflen );
  blake2b_compress( S, S->buf );

  for( i = 0; i < 8; ++i )
    store64( buffer + i * sizeof( S->h[i] ), S->h[i] );

  memcpy( out, buffer, S->outlen );
  secure_zero_memory( buffer, 64 );

  return 0;
}