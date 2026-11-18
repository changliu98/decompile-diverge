int blake2b_init( blake2b_state *S, size_t outlen )
{
  int ret = -1;
  if ( ( !outlen ) || ( outlen > 64 ) )
  {
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