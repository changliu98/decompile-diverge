int __cdecl func0(int n)
{
  int sum = 0;
  
  // Iterate through powers of 2 until the division truncates to 0
  for (int i = 1; n / i > 0; i *= 2)
  {
    sum += n / i;
  }
  
  return sum;
}