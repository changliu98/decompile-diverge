int __cdecl func0(int x, int y, int z)
{
  int j; // [rsp+8h] [rbp-38h]
  int found; // [rsp+Ch] [rbp-34h]
  int i; // [rsp+10h] [rbp-30h]
  int counts[3]; // [rsp+14h] [rbp-2Ch] BYREF
  int unique_values; // [rsp+20h] [rbp-20h]
  int result[3]; // [rsp+24h] [rbp-1Ch]
  int za; // [rsp+30h] [rbp-10h]
  int ya; // [rsp+34h] [rbp-Ch]
  int xa; // [rsp+38h] [rbp-8h]

  xa = x;
  ya = y;
  za = z;
  result[0] = x;
  result[1] = y;
  result[2] = z;
  unique_values = 0;
  memset(counts, 0, sizeof(counts));
  for ( i = 0; i < 3; ++i )
  {
    found = 0;
    for ( j = 0; j < i; ++j )
    {
      if ( result[j] == result[i] )
      {
        found = 1;
        break;
      }
    }
    if ( !found )
      ++unique_values;
  }
  if ( unique_values == 3 )
    return 0;
  else
    return 4 - unique_values;
}