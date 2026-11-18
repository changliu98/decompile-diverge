int __cdecl func0(int n)
{
  int count = 0;
  
  while (n)
  {
    n /= 10;
    ++count;
  }
  
  return count;
}