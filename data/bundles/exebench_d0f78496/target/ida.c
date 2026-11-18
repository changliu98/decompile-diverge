char *__cdecl read_int(char *s, int nr, int *d)
{
  char *v3; // rcx
  bool v5; // [rsp+1h] [rbp-1Dh]
  int result; // [rsp+2h] [rbp-1Ch]

  for ( result = 0; ; result = *v3 - 48 + 10 * result )
  {
    --nr;
    v5 = 0;
    if ( nr >= 0 )
    {
      v5 = 0;
      if ( *s >= 48 )
        v5 = *s <= 57;
    }
    if ( !v5 )
      break;
    v3 = s++;
  }
  *d = result;
  return s;
}