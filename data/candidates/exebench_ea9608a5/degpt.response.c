// Converts a positive integer to its binary representation as a string
// n: the integer to convert
// rbn: pointer to the buffer where the binary string will be stored (in reverse order)
void dec2bin(int number, char *reverse_binary_buffer)
{
  // Loop until n becomes 0
  for (; 0 < number; number = number >> 1) {
    // Extract the least significant bit and store '1' or '0' in the buffer
    // Then increment the pointer to the next position in the buffer
    *reverse_binary_buffer++ = (number & 1U) ? '1' : '0';
  }
}