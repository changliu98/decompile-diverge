void __cdecl strrev(char *p)
{
  bool v1; // [rsp+1h] [rbp-11h]
  char *q; // [rsp+2h] [rbp-10h]
  char *qa; // [rsp+2h] [rbp-10h]
  char *pa; // [rsp+Ah] [rbp-8h]

  pa = p;
  for ( q = p; ; ++q )
  {
    v1 = 0;
    if ( q )
      v1 = *q != 0;
    if ( !v1 )
      break;
  }
  for ( qa = q - 1; pa < qa; --qa )
  {
    *pa ^= *qa;
    *qa ^= *pa;
    *pa++ ^= *qa;
  }
}