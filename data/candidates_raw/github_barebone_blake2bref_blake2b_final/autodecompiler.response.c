int blake2b_final( blake2b_state *S, uint8_t *out, size_t outlen )
{
  if( !out || outlen < S->outlen )
  {
    return -1;
  }

  if( blake2b_is_lastblock( S ) )
  {
    return -1;
  }

  blake2b_increment_counter( S, S->buflen );
  blake2b_set_lastblock( S );
  memset( S->buf + S->buflen, 0, 64 - S->buflen );
  blake2b_compress( S, S->buf );

  size_t i;
  uint8_t buffer[64];
  memset( buffer, 0, sizeof( buffer ) );
  for( i = 0; i < 8; ++i )
  {
    store64( buffer + sizeof( S->h[i] ) * i, S->h[i] );
  }
  memcpy( out, buffer, S->outlen );
  secure_zero_memory( buffer, sizeof( buffer ) );
  return 0;
}