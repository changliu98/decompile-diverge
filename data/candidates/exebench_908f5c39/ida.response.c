int __cdecl gcd_ptr(int *u, int *v)
{
  int *t; // [rsp+0h] [rbp-18h]

  while ( *u > 0 )
  {
    if ( *u < *v )
    {
      t = u;
      u = v;
      v = t;
    }
    *u -= *v;
  }
  return *v;
}