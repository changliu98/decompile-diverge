int __cdecl func0(int n)
{
  int cnt = 0;
  
  for (int i = 1; i <= n; ++i)
  {
    for (int temp = i; temp; temp >>= 1)
    {
      if ((temp & 1) == 0)
        ++cnt;
    }
  }
  
  return cnt;
}