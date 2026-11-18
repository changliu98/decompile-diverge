size_t __cdecl t_add(size_t a, size_t b, int *ok)
{
  size_t v5; // [rsp+8h] [rbp-30h]
  bool v6; // [rsp+1Fh] [rbp-19h]

  v6 = 0;
  if ( *ok )
  {
    if ( a <= b )
      v5 = b;
    else
      v5 = a;
    v6 = b + a >= v5;
  }
  *ok = v6;
  if ( *ok )
    return b + a;
  else
    return 0LL;
}