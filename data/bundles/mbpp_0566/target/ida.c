int __cdecl func0(int n)
{
  if ( n )
    return func0(n / 10) + n % 10;
  else
    return 0;
}