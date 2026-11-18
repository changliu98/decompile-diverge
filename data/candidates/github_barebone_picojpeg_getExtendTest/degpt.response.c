// Returns a 16-bit unsigned integer with the i-th bit set to 1 and all other bits set to 0.
// The input 'i' is expected to be in the range [0, 15].
// The result is masked with 0xFFFF to ensure it fits within a uint16_t.
uint16 getExtendTest(uint8 bit_index)
{
  return (1 << bit_index) & 0xFFFF;
}