void __cdecl norm(int *hi, int *lo, int base)
{
  int n; // [rsp+0h] [rbp-18h]
  int na; // [rsp+0h] [rbp-18h]

  if ( *lo < 0 )
  {
    n = (-*lo - 1) / base + 1;
    *hi -= n;
    *lo += base * n;
  }
  if ( *lo >= base )
  {
    na = *lo / base;
    *hi += na;
    *lo -= base * na;
  }
}