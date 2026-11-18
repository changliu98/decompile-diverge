int __cdecl compter_mots(char *saisie, size_t *lenght)
{
  size_t lenght_max; // [rsp+0h] [rbp-30h]
  size_t lenght_current; // [rsp+8h] [rbp-28h]
  int gui; // [rsp+10h] [rbp-20h]
  int words; // [rsp+14h] [rbp-1Ch]
  char *p; // [rsp+18h] [rbp-18h]
  char *pa; // [rsp+18h] [rbp-18h]

  words = 0;
  gui = 0;
  lenght_current = 0LL;
  lenght_max = 0LL;
  for ( p = strchr(saisie, 0) - 1; *p == 32; --p )
    *p = 0;
  for ( pa = saisie; *pa == 32; ++pa )
    ;
  if ( *pa )
    words = 1;
  while ( *pa )
  {
    if ( *pa == 34 || *pa == 39 )
    {
      gui = gui == 0;
    }
    else if ( *pa != 32 || gui )
    {
      ++lenght_current;
    }
    else
    {
      if ( lenght_current > lenght_max )
        lenght_max = lenght_current;
      lenght_current = 0LL;
      ++words;
      while ( *pa == 32 )
        ++pa;
      --pa;
    }
    ++pa;
  }
  if ( lenght_current > lenght_max )
    lenght_max = lenght_current;
  *lenght = lenght_max;
  return words;
}