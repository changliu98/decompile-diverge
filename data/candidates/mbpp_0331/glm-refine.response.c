int __cdecl func0(int n)
{
  int count = 0;
  
  // Iterate through each bit position of 'n'
  for (int bit = 1; bit <= n; bit <<= 1)
  {
    // If the current bit is not set (0), increment the counter
    if ((n & bit) == 0)
      ++count;
  }
  
  return count;
}