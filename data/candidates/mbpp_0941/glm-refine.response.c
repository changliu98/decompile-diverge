int __cdecl func0(int *num, int size)
{
  int count = 0;
  
  for (int i = 0; i < size && num[i] != -1; ++i)
    ++count;
    
  return count;
}