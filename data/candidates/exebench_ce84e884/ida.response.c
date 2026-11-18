void __cdecl get_grid_address(long *address, const long *address_double, const long *PS)
{
  int i; // [rsp+0h] [rbp-1Ch]

  for ( i = 0; i < 3; ++i )
    address[i] = (address_double[i] - PS[i]) / 2;
}