void __cdecl heaviside(const double *first, const double *last, double *res)
{
  bool v3; // [rsp+1h] [rbp-21h]
  int i; // [rsp+2h] [rbp-20h]

  *res = 1.0;
  for ( i = 0; i < (int)(last - first + 1); ++i )
  {
    v3 = 0;
    if ( *res == 1.0 )
      v3 = first[i] >= 0.0;
    *res = (double)v3;
  }
}