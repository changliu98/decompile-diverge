int __cdecl func0(int n)
{
  int i;
  int result;

  if (n < 1)
    return 0;
    
  if (n == 1)
    return 1;

  result = 18;
  for (i = 2; i < n; ++i)
    result *= 10;

  return result;
}