int __cdecl func0(int p, int q, int N)
{
  int digit; // Uninitialized if N <= 0, matching the original behavior
  int temp;

  // Loop exactly N times to find the N-th digit after the decimal point
  while (N-- > 0)
  {
    temp = 10 * p;          // Shift the remainder left by one decimal place
    digit = temp / q;       // Extract the next decimal digit
    p = temp % q;           // Calculate the new remainder for the next iteration
  }

  return digit;
}