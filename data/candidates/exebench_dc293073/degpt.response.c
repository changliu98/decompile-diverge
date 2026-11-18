char * Q_strupr(char *input_string)
{
  // Iterate through each character of the string until the null terminator is reached
  for (char *current_char_ptr = input_string; *current_char_ptr != '\0'; current_char_ptr++) {
    // Check if the character is a lowercase ASCII letter (between '`' and '{')
    if (*current_char_ptr > '`' && *current_char_ptr < '{') {
      // Convert the lowercase letter to uppercase by subtracting 0x20 (32)
      *current_char_ptr -= 0x20;
    }
  }
  // Return the original pointer to the modified string
  return input_string;
}