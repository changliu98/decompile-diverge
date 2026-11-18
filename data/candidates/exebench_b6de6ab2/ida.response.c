void __cdecl reduce_grid_address(int *address, const int *mesh)
{
  int i; // [rsp+4h] [rbp-14h]

  for ( i = 0; i < 3; ++i )
    address[i] -= (address[i] > mesh[i] / 2) * mesh[i];
}