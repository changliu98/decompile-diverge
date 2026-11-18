bool __cdecl func0(int *arraynums, int length)
{
  int j; // [rsp+0h] [rbp-18h]
  int i; // [rsp+4h] [rbp-14h]
  char found_duplicate; // [rsp+Bh] [rbp-Dh]

  found_duplicate = 0;
  for ( i = 0; i < length; ++i )
  {
    for ( j = i + 1; j < length; ++j )
    {
      if ( arraynums[i] == arraynums[j] )
      {
        found_duplicate = 1;
        break;
      }
    }
    if ( (found_duplicate & 1) != 0 )
      break;
  }
  return found_duplicate;
}