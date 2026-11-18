/**
 * Converts a null-terminated string to uppercase in-place.
 * 
 * @param str Pointer to the string to be converted.
 */
void toUpperCase(char *inputString)
{
  // Iterate through each character until the null terminator is reached
  for (; *inputString != '\0'; inputString++) {
    // Check if the character is a lowercase ASCII letter (between 'a' and 'z')
    // '`' is the ASCII character before 'a', and '{' is the character after 'z'
    if (*inputString > '`' && *inputString < '{') {
      // Convert lowercase to uppercase by subtracting 0x20 (32 in decimal)
      // This works because uppercase and lowercase ASCII letters differ by 32
      *inputString -= 0x20;
    }
  }
}