int blake2b_init( blake2b_state *S, size_t outlen )
{
  int ret;

  if ( ( !S ) || ( outlen == 0 ) || ( outlen > 64 ) )
  {
    if ( S ) blake2b_invalidate_state( S );
    ret = -1;
  }
  else
  {
    const blake2b_param P =
    {
      ( uint8_t ) outlen,
      0,
      1,
      1,
      0,
      0,
      0,
      0,
      {0},
      {0},
      {0}
    };
    ret = blake2b_init_param( S, &P );
  }

  return ret;
}