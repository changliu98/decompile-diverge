// Checks if the given unsigned long value, when interpreted as a signed integer, is negative.
// This effectively detects if the most significant bit (sign bit) is set.
bool pmc_overflow(unsigned_long value)
{
  // Cast val to int to check the sign bit, then cast to uint to return 1 if negative, 0 otherwise.
  return (uint)((int)value < 0);
}