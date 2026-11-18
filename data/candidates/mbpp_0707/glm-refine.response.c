// This function calculates the total number of 1-bits in the binary 
// representations of all integers from 0 to n (inclusive).
// It uses a bitwise dynamic programming approach by evaluating the 
// contribution of each bit position (powers of 2) to the total sum.
int __cdecl count_set_bits_up_to_n(int n)
{
  int upper_bound = n + 1;   // We count from 0 to n, which is (n + 1) numbers
  int power_of_2 = 2;        // Represents the current bit position's weight (2^k)
  int total_ones = upper_bound / 2; // Count of 1s in the least significant bit (LSB)

  // Iterate through each bit position (2^1, 2^2, 2^3, ...)
  while (power_of_2 <= upper_bound)
  {
    // Number of complete pairs of blocks for the current bit position.
    // Each complete pair contributes exactly 'power_of_2' set bits.
    int complete_pairs = (upper_bound / power_of_2) / 2;
    total_ones += power_of_2 * complete_pairs;

    // If there is an incomplete pair remaining, it means the current bit 
    // is 1 for a partial block. We add the remaining elements as set bits.
    if ((upper_bound / power_of_2) & 1)
    {
      total_ones += upper_bound % power_of_2;
    }

    power_of_2 *= 2;
  }

  return total_ones;
}