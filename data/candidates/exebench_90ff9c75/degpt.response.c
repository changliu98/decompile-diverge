// Converts a 16-bit unsigned integer to a 4-character hexadecimal string
// Parameters:
//   Number - The unsigned integer to convert
//   String - Pointer to a buffer of at least 5 bytes to store the result
void WordToHex(uint value, char *buffer)
{
  // Iterate through each of the 4 hex digits, from most significant to least significant
  for (int index = 3; index >= 0; index--) {
    // Extract the least significant 4 bits (one hex digit)
    char nibble = value & 0xf;
    // Convert the nibble to its ASCII character representation
    // Digits 0-9 are converted to '0'-'9', values 10-15 are converted to 'a'-'f'
    buffer[index] = nibble < 10 ? nibble + '0' : nibble + '7';
    // Shift right by 4 bits to process the next hex digit
    value >>= 4;
  }
  // Null-terminate the resulting string
  buffer[4] = '\0';
}