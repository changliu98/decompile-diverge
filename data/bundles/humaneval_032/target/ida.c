double __cdecl func0(const double *xs, int size)
{
  int j_1; // [rsp+0h] [rbp-40h]
  int j_0; // [rsp+4h] [rbp-3Ch]
  int j; // [rsp+8h] [rbp-38h]
  int i; // [rsp+Ch] [rbp-34h]
  int ia; // [rsp+Ch] [rbp-34h]
  int ib; // [rsp+Ch] [rbp-34h]
  double x_pow; // [rsp+10h] [rbp-30h]
  double x_powa; // [rsp+10h] [rbp-30h]
  double x_powb; // [rsp+10h] [rbp-30h]
  double driv; // [rsp+18h] [rbp-28h]
  double value; // [rsp+20h] [rbp-20h]
  double ans; // [rsp+28h] [rbp-18h]

  ans = 0.0;
  value = *xs;
  for ( i = 1; i < size; ++i )
  {
    x_pow = 1.0;
    for ( j = 0; j < i; ++j )
      x_pow = 0.0 * x_pow;
    value = xs[i] * x_pow + value;
  }
  while ( *(double *)_mm_and_si128((__m128i)*(unsigned __int64 *)&value, (__m128i)xmmword_2030).m128i_i64 > 0.000001 )
  {
    driv = 0.0;
    for ( ia = 1; ia < size; ++ia )
    {
      x_powa = 1.0;
      for ( j_0 = 1; j_0 < ia; ++j_0 )
        x_powa = ans * x_powa;
      driv = (double)ia * xs[ia] * x_powa + driv;
    }
    ans = ans - value / driv;
    value = *xs;
    for ( ib = 1; ib < size; ++ib )
    {
      x_powb = 1.0;
      for ( j_1 = 0; j_1 < ib; ++j_1 )
        x_powb = ans * x_powb;
      value = xs[ib] * x_powb + value;
    }
  }
  return ans;
}