// Converts a hexadecimal character to its integer value.
// Returns 0 for invalid characters.
int hex_digit_to_int(char hex_char)
{
  // Handle digits '0' through '9'
  if (hex_char >= '0' && hex_char <= '9')
    return hex_char - '0';
  // Handle lowercase hex digits 'a' through 'f'
  if (hex_char >= 'a' && hex_char <= 'f')
    return hex_char - 'a' + 10;
  // Handle uppercase hex digits 'A' through 'F'
  if (hex_char >= 'A' && hex_char <= 'F')
    return hex_char - 'A' + 10;
  // Return 0 for invalid input
  return 0;
}