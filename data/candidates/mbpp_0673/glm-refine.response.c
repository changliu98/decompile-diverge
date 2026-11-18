int __cdecl func0(int *list, int size)
{
  int res = 0;
  
  for (int i = 0; i < size; ++i)
  {
    res = list[i] + 10 * res;
  }
  
  return res;
}