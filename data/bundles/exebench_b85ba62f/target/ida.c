unsigned __int64 __cdecl rational_best_approximation(
        unsigned __int64 given_numerator,
        unsigned __int64 given_denominator,
        unsigned __int64 max_numerator,
        unsigned __int64 max_denominator,
        unsigned __int64 *best_numerator,
        unsigned __int64 *best_denominator)
{
  unsigned __int64 a; // [rsp+0h] [rbp-70h]
  unsigned __int64 t; // [rsp+8h] [rbp-68h]
  unsigned __int64 ta; // [rsp+8h] [rbp-68h]
  unsigned __int64 tb; // [rsp+8h] [rbp-68h]
  unsigned __int64 d1; // [rsp+10h] [rbp-60h]
  unsigned __int64 n1; // [rsp+18h] [rbp-58h]
  unsigned __int64 d0; // [rsp+20h] [rbp-50h]
  unsigned __int64 n0; // [rsp+28h] [rbp-48h]

  d1 = 0LL;
  n0 = 0LL;
  d0 = 1LL;
  n1 = 1LL;
  while ( n1 <= max_numerator && d1 <= max_denominator )
  {
    if ( !given_denominator )
      goto LABEL_7;
    t = given_denominator;
    a = given_numerator / given_denominator;
    given_denominator = given_numerator % given_denominator;
    given_numerator = t;
    ta = n1 * a + n0;
    n0 = n1;
    n1 = ta;
    tb = d1 * a + d0;
    d0 = d1;
    d1 = tb;
  }
  n1 = n0;
  d1 = d0;
LABEL_7:
  *best_numerator = n1;
  *best_denominator = d1;
  return 0LL;
}