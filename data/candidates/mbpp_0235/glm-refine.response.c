int __cdecl func0(int n)
{
  int res = 0;
  int count = 0;

  // Iterate through each bit of 'n' from least to most significant
  for (int temp = n; temp > 0; temp >>= 1)
  {
    // If the current bit index 'count' is odd, set that bit in 'res'
    if (count & 1)
      res |= (1 << count);
    count++;
  }

  // Combine the original number with the generated mask
  return res | n;
}