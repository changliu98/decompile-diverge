int __cdecl func0(int x, int y)
{
  int i; // [rsp+8h] [rbp-18h]
  int z; // [rsp+Ch] [rbp-14h]
  int result; // [rsp+10h] [rbp-10h]
  int n; // [rsp+14h] [rbp-Ch]

  n = ngcd(x, y);
  result = 0;
  z = (int)sqrt((double)n);
  for ( i = 1; i <= z; ++i )
  {
    if ( !(n % i) )
    {
      result += 2;
      if ( i == n / i )
        --result;
    }
  }
  return result;
}