void __cdecl reverse(char *s)
{
  char temp;
  char *left;
  char *right;

  // Find the null terminator to determine the end of the string
  right = s;
  while (*right)
    ++right;

  // Set 'right' to the last valid character (just before the null terminator)
  for (right = right - 1, left = s; left < right; --right, ++left)
  {
    // Swap characters at the 'left' and 'right' pointers
    temp = *left;
    *left = *right;
    *right = temp;
  }
}