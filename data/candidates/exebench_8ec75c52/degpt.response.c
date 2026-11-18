// Converts the input string to uppercase in-place.
void strupr(char *inputString)
{
  // Iterate through each character of the string until the null terminator is reached.
  for (; *inputString; inputString++) {
    // Check if the character is a lowercase ASCII letter ('a'-'z').
    // '`' is the ASCII value for '`' (96), and '{' is the ASCII value for '{' (123).
    // Lowercase letters fall between these values.
    if (*inputString > '`' && *inputString < '{') {
      // Convert the lowercase letter to uppercase by subtracting 0x20 (32).
      // In ASCII, uppercase letters are 32 less than their lowercase counterparts.
      *inputString -= 0x20;
    }
  }
}