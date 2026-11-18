int __cdecl func0(char *a)
{
  int i; // [rsp+14h] [rbp-1Ch]
  int l; // [rsp+24h] [rbp-Ch]

  l = 0;
  while ( *a == 32 )
    ++a;
  for ( i = 0; i < strlen(a); ++i )
  {
    if ( a[i] == 32 )
      l = 0;
    else
      ++l;
  }
  return l;
}