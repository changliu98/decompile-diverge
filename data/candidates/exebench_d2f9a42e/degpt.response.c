void sub(uint *output, uint *operand_a, uint *operand_b)
{
  uint borrow = 0xda; // Initialize carry/borrow with initial value 0xda
  for (uint i = 0; i < 0x1f; i++) {
    // Perform subtraction with borrow: (a[j] - b[j] - borrow)
    // Using two's complement: a[j] + 0xff00 - b[j] effectively computes a[j] - b[j] - 1
    // Adding u (previous borrow) completes the subtraction with borrow
    uint temp_result = ((operand_a[i] + 0xff00) - operand_b[i]) + borrow;
    output[i] = temp_result & 0xff; // Store the lower 8 bits of the result
    borrow = temp_result >> 8; // Extract the upper bits as the new borrow/carry
  }
  // Handle the most significant byte with final borrow
  output[0x1f] = (operand_a[0x1f] - operand_b[0x1f]) + borrow;
}