int __cdecl func0(int n)
{
  int v2; // [rsp+4h] [rbp-1Ch]
  int temp; // [rsp+Ch] [rbp-14h]
  int x; // [rsp+10h] [rbp-10h]
  int res; // [rsp+14h] [rbp-Ch]

  if ( n <= 3 )
    return n;
  res = n;
  for ( x = 1; x <= n; ++x )
  {
    temp = x * x;
    if ( x * x > n )
      break;
    if ( res >= func0(n - temp) + 1 )
      v2 = func0(n - temp) + 1;
    else
      v2 = res;
    res = v2;
  }
  return res;
}