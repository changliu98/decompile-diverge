__int64 __cdecl func0(float *lst, int lst_size)
{
  __int64 sum = 0LL;
  
  for (int i = 0; i < lst_size; ++i)
  {
    double val = lst[i];
    double frac = val - round(val);
    
    // Check if the number is effectively an integer (fractional part is ~0)
    if (fabs(frac) < 0.0001 && val > 0.0)
    {
      int rounded_val = (int)round(val);
      
      // Check if the integer is odd
      if (rounded_val % 2 == 1)
      {
        sum += rounded_val * rounded_val;
      }
    }
  }
  
  return sum;
}