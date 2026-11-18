int __cdecl func0(int *listval, int size)
{
  int max_val = INT_MIN; // 0x80000000 is the minimum value for a 32-bit signed integer

  for (int i = 0; i < size; ++i)
  {
    if (listval[i] > max_val)
    {
      max_val = listval[i];
    }
  }
  
  return max_val;
}