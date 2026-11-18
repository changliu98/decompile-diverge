int hexchar(int char_code)
{
  // Check if the character is a digit between '0' and '9'
  if (char_code >= '0' && char_code <= '9')
    return char_code - '0'; // Return the numeric value of the digit

  // Check if the character is a lowercase hexadecimal digit between 'a' and 'f'
  if (char_code >= 'a' && char_code <= 'f')
    return char_code - 'a' + 10; // Return the numeric value (10-15)

  // Check if the character is an uppercase hexadecimal digit between 'A' and 'F'
  if (char_code >= 'A' && char_code <= 'F')
    return char_code - 'A' + 10; // Return the numeric value (10-15)

  // Return -1 if the character is not a valid hexadecimal digit
  return -1;
}