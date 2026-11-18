int __cdecl func0(int *lst, int size)
{
  int sum = 0;
  
  // Iterate over every other element (even indices)
  for (int i = 0; i < size; i += 2)
  {
    if (lst[i] % 2 == 1)
      sum += lst[i];
  }
  
  return sum;
}