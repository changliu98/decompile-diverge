int __cdecl getPossibleCount(int *values, int *out_val)
{
  int count = 0;

  for (int i = 0; i < 9; ++i)
  {
    if (values[i])
    {
      ++count;
      if (out_val)
      {
        *out_val = values[i];
      }
    }
  }
  
  return count;
}