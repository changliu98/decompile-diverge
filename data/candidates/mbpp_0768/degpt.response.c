int func0(int value)
{
  int set_bit_count = 0; // Initialize parity counter to 0
  while (value) { // Loop until all bits are processed
    set_bit_count++; // Increment parity for each set bit
    value &= value - 1U; // Clear the least significant bit set
  }
  return set_bit_count % 2; // Return 1 if odd number of set bits, 0 otherwise
}