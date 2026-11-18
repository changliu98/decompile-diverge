char *__cdecl maybeint(char *q, int *dst)
{
  char *v2; // rcx
  bool v4; // [rsp+1h] [rbp-15h]
  int num; // [rsp+2h] [rbp-14h]
  char *qa; // [rsp+Eh] [rbp-8h]

  qa = q;
  if ( *q < 48 || *q > 57 )
  {
    *dst = 0;
  }
  else
  {
    for ( num = 0; ; num = *v2 - 48 + 10 * num )
    {
      v4 = 0;
      if ( *qa >= 48 )
        v4 = *qa <= 57;
      if ( !v4 )
        break;
      v2 = qa++;
    }
    *dst = num;
  }
  return qa;
}