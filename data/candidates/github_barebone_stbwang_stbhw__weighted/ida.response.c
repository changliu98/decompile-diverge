int __cdecl stbhw__weighted(int num_options, int *weights)
{
  int choice; // [rsp+4h] [rbp-1Ch]
  int total; // [rsp+8h] [rbp-18h]
  int totala; // [rsp+8h] [rbp-18h]
  int k; // [rsp+Ch] [rbp-14h]
  int ka; // [rsp+Ch] [rbp-14h]

  total = 0;
  for ( k = 0; k < num_options; ++k )
    total += weights[k];
  choice = (rand() >> 4) % total;
  totala = 0;
  for ( ka = 0; ka < num_options; ++ka )
  {
    totala += weights[ka];
    if ( choice < totala )
      break;
  }
  if ( ka >= num_options )
    _assert_fail("k < num_options", "func.c", 0x294u, "int stbhw__weighted(int, int *)");
  return ka;
}