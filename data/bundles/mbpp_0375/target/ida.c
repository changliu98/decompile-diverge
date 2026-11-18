int __cdecl func0(int n, int m)
{
  if ( n % m <= m + m * (n / m) - n )
    return m * (n / m);
  else
    return m + m * (n / m);
}