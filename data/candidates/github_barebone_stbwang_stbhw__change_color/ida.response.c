int __cdecl stbhw__change_color(int old_color, int num_options, int *weights)
{
  int choice; // [rsp+Ch] [rbp-24h]
  int total; // [rsp+10h] [rbp-20h]
  int totala; // [rsp+10h] [rbp-20h]
  int k; // [rsp+14h] [rbp-1Ch]
  int ka; // [rsp+14h] [rbp-1Ch]

  if ( !weights )
    return ((rand() >> 4) % (num_options - 1) + 1 + old_color) % num_options;
  total = 0;
  for ( k = 0; k < num_options; ++k )
  {
    if ( k != old_color )
      total += weights[k];
  }
  choice = (rand() >> 4) % total;
  totala = 0;
  for ( ka = 0; ka < num_options; ++ka )
  {
    if ( ka != old_color )
    {
      totala += weights[ka];
      if ( choice < totala )
        break;
    }
  }
  if ( ka >= num_options )
    _assert_fail("k < num_options", "func.c", 0x2A9u, "int stbhw__change_color(int, int, int *)");
  return ka;
}