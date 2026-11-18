int func0(char *input_string)
{
  int character_count = 0; // Initialize counter to zero
  for (; *input_string != '\0'; input_string++) { // Iterate through the string until the null terminator
    character_count++; // Increment the count for each character
  }
  return character_count; // Return the total number of characters in the string
}