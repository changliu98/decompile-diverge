int __cdecl func0(float *lst, int size)
{
  int sum = 0;
  
  for (int i = 0; i < size; ++i)
  {
    int ceiled_val = (int)ceil(lst[i]);
    sum += ceiled_val * ceiled_val;
  }
  
  return sum;
}