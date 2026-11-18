// Function to check if the number of set bits in x is odd
_Bool func0(int value)
{
  // Returns 1 if the number of set bits in x is odd, 0 otherwise
  return __builtin_parity(value);
}