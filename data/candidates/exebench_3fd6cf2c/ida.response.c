void __cdecl od_filter_dering_direction_offsets(int *offset, int dir, int bstride)
{
  int k; // [rsp+8h] [rbp-14h]
  int ka; // [rsp+8h] [rbp-14h]

  if ( dir > 4 )
  {
    for ( ka = 1; ka <= 3; ++ka )
      offset[ka - 1] = ka * (6 - dir) / 2 + bstride * ka;
  }
  else
  {
    for ( k = 1; k <= 3; ++k )
      offset[k - 1] = k + bstride * (k * (dir - 2) / 2);
  }
}