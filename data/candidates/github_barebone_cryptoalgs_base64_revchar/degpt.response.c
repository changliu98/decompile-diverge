// Reverses a character by mapping it to its corresponding index in a custom base64-like alphabet.
// Handles uppercase letters, lowercase letters, digits, and specific symbols.
BYTE revchar(char inputChar)
{
  // Map uppercase letters 'A'-'Z' to indices 0-25
  if ((inputChar >= 'A') && (inputChar <= 'Z')) {
    return inputChar - 0x41;
  }
  // Map lowercase letters 'a'-'z' to indices 26-51
  if ((inputChar >= 'a') && (inputChar <= 'z')) {
    return inputChar - 0x47;
  }
  // Map digits '0'-'9' to indices 52-61
  if ((inputChar >= '0') && (inputChar <= '9')) {
    return inputChar + 4;
  }
  // Map '+' to '>'
  if (inputChar == '+') {
    return '>';
  }
  // Map '/' to '?'
  if (inputChar == '/') {
    return '?';
  }
  // Return the character unchanged if it doesn't match any known mapping
  return inputChar;
}