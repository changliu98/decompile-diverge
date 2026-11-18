int blake2b_init( blake2b_state *S, size_t outlen )
{
  blake2b_param P[1];

  if( !S || !outlen || outlen > 64 ) return -1;

  P->digest_length = (uint8_t)outlen;
  P->key_length    = 0;
  P->fanout        = 1;
  P->depth         = 1;
  P->leaf_length   = 0;
  P->node_offset   = 0;
  P->node_depth    = 0;
  P->inner_length   = 0;
  memset( P->reserved, 0, 14 );
  memset( P->salt,     0, 16 );
  memset( P->personal, 0, 16 );
  return blake2b_init_param( S, P );
}