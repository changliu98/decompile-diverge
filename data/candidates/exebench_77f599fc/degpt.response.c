void uppercaser(char *inputString)
{
  // Iterate through each character of the string until the null terminator
  for (int index = 0; inputString[index] != '\0'; index++) {
    // Check if the character is a lowercase letter (ASCII range 'a' to 'z')
    // '`' is ASCII 96, '{' is ASCII 123; characters between them are 'a'-'z'
    if (inputString[index] > '`' && inputString[index] < '{') {
      // Convert lowercase to uppercase by subtracting 0x20 (32 in decimal)
      // This works because uppercase letters are 32 ASCII values before their lowercase counterparts
      inputString[index] -= 0x20;
    }
  }
}