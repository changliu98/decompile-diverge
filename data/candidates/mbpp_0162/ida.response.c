int __cdecl func0(int n)
{
  if ( n >= 1 )
    return func0(n - 2) + n;
  else
    return 0;
}