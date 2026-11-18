const char *__cdecl func0(int n)
{
  int count = 0;
  int limit = (int)sqrt((double)n) + 2;
  
  for (int i = 1; i < limit; ++i)
  {
    if (n % i == 0)
    {
      if (n / i == i)
        ++count;
      else
        count += 2;
    }
  }
  
  return (count & 1) ? "Odd" : "Even";
}