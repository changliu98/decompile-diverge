int __cdecl summe(int *n, int *s)
{
  bool v3; // [rsp+Fh] [rbp-11h]

  v3 = 1;
  if ( *n )
  {
    *s += (*n)--;
    return summe(n, s) != 0;
  }
  return v3;
}