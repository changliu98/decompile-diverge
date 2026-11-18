int a2d(char hex_char)
{
  // Convert hexadecimal character '0'-'9' to integer value 0-9
  if (hex_char >= '0' && hex_char <= '9') return hex_char - '0';
  // Convert lowercase hexadecimal character 'a'-'f' to integer value 10-15
  if (hex_char >= 'a' && hex_char <= 'f') return hex_char - 'a' + 10;
  // Convert uppercase hexadecimal character 'A'-'F' to integer value 10-15
  if (hex_char >= 'A' && hex_char <= 'F') return hex_char - 'A' + 10;
  // Return -1 if the character is not a valid hexadecimal digit
  return -1;
}