// Converts integer x to a string representation in the given base
// Stores the result in the output buffer 'out'
void func0(int number, int radix, char *output_buffer)
{
  char reversed_digits[33]; // Temporary buffer to store digits in reverse order
  int digit_count = 0; // Index for the temporary buffer

  // Extract digits from x in reverse order (least significant first)
  for (; 0 < number; number = number / radix) {
    reversed_digits[digit_count] = (char)(number % radix) + '0'; // Convert digit to ASCII character
    digit_count = digit_count + 1; // Move to next position in temp buffer
  }

  int output_index = 0; // Index for the output buffer

  // Copy digits from temp buffer to output buffer in correct order (most significant first)
  while (0 < digit_count) {
    digit_count = digit_count + -1; // Decrement index to access previous digit
    output_buffer[output_index] = reversed_digits[digit_count]; // Copy digit to output buffer
    output_index = output_index + 1; // Move to next position in output buffer
  }

  output_buffer[output_index] = '\0'; // Null-terminate the output string
}