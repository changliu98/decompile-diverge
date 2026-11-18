int __cdecl cpy(char *a, char *b)
{
  bool v3; // [rsp+1h] [rbp-15h]
  int i; // [rsp+2h] [rbp-14h]

  for ( i = 0; ; ++i )
  {
    v3 = 0;
    if ( b[i] )
      v3 = i < 100;
    if ( !v3 )
      break;
    a[i] = b[i];
  }
  a[i] = 0;
  return 0;
}