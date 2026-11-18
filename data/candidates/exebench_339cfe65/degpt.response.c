void toggle(int *value)
{
  // Toggle the value of v to 1 if it is 0, or 0 if it is non-zero.
  // The expression (*v != 0) evaluates to 1 if *v is non-zero, 0 otherwise.
  // XORing with 0xffU flips all bits, but since the result is only 0 or 1,
  // this effectively flips the bit: 1 ^ 0xffU has LSB 0, 0 ^ 0xffU has LSB 1.
  // ANDing with 1 extracts the least significant bit, ensuring the result is 0 or 1.
  *value = (uint)((*value != 0 ^ 0xffU) & 1);
}