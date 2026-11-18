unsigned int __cdecl mul_poly(unsigned int operand_a, unsigned int operand_b, unsigned int poly)
{
  unsigned int result = 0;

  while (operand_a)
  {
    // If the lowest bit of operand_a is set, XOR the current operand_b into the result
    if (operand_a & 1)
      result ^= operand_b;

    // Shift operand_a right to process the next bit
    operand_a >>= 1;

    // Shift operand_b left (multiply by 2)
    operand_b <<= 1;

    // If operand_b exceeds 16 bits, reduce it using the polynomial
    if (operand_b & (1 << 16))
      operand_b ^= poly;
  }

  return result;
}