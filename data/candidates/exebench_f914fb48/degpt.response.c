// Converts the input string to uppercase in-place.
void strupper(char *str)
{
  // Iterate through each character of the string until the null terminator.
  for (int idx = 0; str[idx] != '\0'; idx++) {
    // Check if the character is a lowercase letter (ASCII 'a' to 'z').
    // '`' is ASCII 96, '{' is ASCII 123. Lowercase letters are between 97 and 122.
    if (str[idx] > '`' && str[idx] < '{') {
      // Convert lowercase to uppercase by subtracting 0x20 (32 in decimal).
      str[idx] -= 0x20;
    }
  }
}