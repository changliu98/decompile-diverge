// Checks if the string starts with '>' (indicating end of GCG data)
// and resets the addend to 0.
// Returns 1 if the first character is '>', 0 otherwise.
int endGCGdata(char *str, int *offset)
{
  // Reset the addend value to 0
  *offset = 0;
  // Return 1 if the current character is '>', 0 otherwise
  return (int)(*str == '>');
}