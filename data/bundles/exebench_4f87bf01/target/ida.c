void __cdecl reduce_grid_address(long *address, const long *mesh)
{
  long i; // [rsp+8h] [rbp-18h]

  for ( i = 0LL; i < 3; ++i )
    address[i] -= (address[i] > mesh[i] / 2) * mesh[i];
}