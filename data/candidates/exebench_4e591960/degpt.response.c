void numconv(char *str)
{
  // Iterate through the string until the null terminator is reached
  while (*str != '\0') {
    // Convert ASCII character to its integer value by subtracting '0' (0x30)
    *str += -0x30;
    // Move to the next character in the string
    str++;
  }
}