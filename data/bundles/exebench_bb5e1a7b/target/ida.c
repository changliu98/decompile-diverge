char *__cdecl ReadNumber(char *s, double *num)
{
  char *v2; // rcx
  char *v3; // rcx
  bool v5; // [rsp+1h] [rbp-33h]
  bool v6; // [rsp+2h] [rbp-32h]
  bool v7; // [rsp+3h] [rbp-31h]
  int x2; // [rsp+4h] [rbp-30h]
  int x1; // [rsp+8h] [rbp-2Ch]
  double minus; // [rsp+Ch] [rbp-28h]
  double x3; // [rsp+14h] [rbp-20h]

  minus = 1.0;
  while ( 1 )
  {
    v7 = 1;
    if ( *s != 43 )
      v7 = *s == 45;
    if ( !v7 )
      break;
    if ( *s == 45 )
      *(_QWORD *)&minus ^= 0x8000000000000000LL;
    ++s;
  }
  x2 = 0;
  x1 = 0;
  x3 = 1.0;
  while ( 1 )
  {
    v6 = 0;
    if ( *s <= 57 )
      v6 = *s >= 48;
    if ( !v6 )
      break;
    v2 = s++;
    x1 = *v2 + 10 * x1 - 48;
  }
  if ( *s )
  {
    if ( *s == 46 )
    {
      ++s;
      while ( 1 )
      {
        v5 = 0;
        if ( *s >= 48 )
          v5 = *s <= 57;
        if ( !v5 )
          break;
        v3 = s++;
        x2 = *v3 + 10 * x2 - 48;
        x3 = 10.0 * x3;
      }
    }
    *num = minus * ((double)x1 + (double)x2 / x3);
    return s;
  }
  else
  {
    *num = (double)x1 * minus;
    return s;
  }
}