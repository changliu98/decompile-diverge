int __cdecl func0(int start, int end)
{
  int i;
  int last_digit = 1;

  // If the range is empty, the product is 1.
  if (start == end)
    return 1;

  // In any sequence of 5 or more consecutive integers, there is guaranteed to be 
  // at least one multiple of 5 and at least one even number. 
  // Their product will always be a multiple of 10, meaning the last digit is 0.
  if (end - start >= 5)
    return 0;

  // Calculate the last digit of the product iteratively.
  // Keeping only the last digit at each step is semantically identical to taking 
  // the modulo 10 of the full product, but prevents integer overflow.
  for (i = start + 1; i <= end; ++i)
    last_digit = (last_digit * (i % 10)) % 10;

  return last_digit;
}