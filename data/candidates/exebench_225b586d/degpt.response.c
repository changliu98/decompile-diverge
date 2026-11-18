// Checks if the string ends with '>' and resets addend to 0
// Returns 1 if the first character is '>', 0 otherwise
int endPearson(char *str, int *counter)
{
  // Reset the addend value to 0
  *counter = 0;
  // Return 1 if the current character is '>', 0 otherwise
  return (int)(*str == '>');
}