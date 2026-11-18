char * func0(char *input_string)
{
  // Iterate through each character in the string until the null terminator
  for (int index = 0; input_string[index] != '\0'; index++) {
    // If the current character is a space, comma, or period
    if (input_string[index] == ' ' || input_string[index] == ',' || input_string[index] == '.') {
      // Replace it with a colon
      input_string[index] = ':';
    }
  }
  // Return the modified string
  return input_string;
}