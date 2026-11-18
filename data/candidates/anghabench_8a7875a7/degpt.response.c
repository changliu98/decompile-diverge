// Converts a single byte value to its hexadecimal character representation.
// Returns '0'-'9' for values 0-9, 'A'-'F' for values 10-15, and '?' for invalid values.
char hex_char(uchar byte_value)
{
  // If the value is between 0 and 9, convert to corresponding digit character
  if (byte_value < 10) {
    return byte_value + '0';
  }
  // If the value is between 10 and 15, convert to corresponding hex letter character
  else if (byte_value < 0x10) {
    return byte_value + 'W';
  }
  // For any value outside the range 0-15, return a placeholder character
  else {
    return '?';
  }
}