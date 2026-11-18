long __cdecl func0(int n)
{
  long sum = 0;
  
  // The loop computes the sum of 2 * i^5 for i from 1 to n.
  // 2 * i * i * i * i * i is optimized to 2 * i^5.
  for (int i = 1; i <= n; ++i)
    sum += 2 * (long)i * i * i * i * i;
    
  return sum;
}