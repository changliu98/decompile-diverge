uint8_t __cdecl gfmul(uint8_t a, uint8_t b)
{
  uint8_t result = 0;

  while (b != 0)
  {
    // If the lowest bit of b is set, add a to the result (XOR in GF(2^8))
    if (b & 1)
      result ^= a;

    // Multiply a by x (left shift by 1)
    a <<= 1;

    // If a overflowed past 8 bits, reduce it modulo the AES polynomial
    if (a & 0x80)          // Equivalent to checking the shifted-out bit
      a ^= 0x1D;           // 0x1D is 29 in decimal

    // Divide b by x (right shift by 1)
    b >>= 1;
  }

  return result;
}