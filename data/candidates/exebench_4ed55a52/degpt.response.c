void shift_array(char *str)
{
  // Iterate through the string until the null terminator is reached
  while (*str != '\0') {
    // Shift each character by 5 positions in the ASCII table
    *str += '\x05';
    // Move to the next character in the array
    str++;
  }
}