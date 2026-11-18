int __cdecl epindex_to_epnum(int epindex, int *epdir)
{
  int dir_in; // [rsp+0h] [rbp-14h]

  dir_in = epindex % 2;
  if ( epdir )
    *epdir = dir_in;
  return (dir_in + epindex) / 2;
}