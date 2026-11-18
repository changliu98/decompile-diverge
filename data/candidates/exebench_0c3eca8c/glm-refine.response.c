void __cdecl expand(char *compacted, char *expanded)
{
  int i = 0;
  char start = compacted[0];
  char end = compacted[2];

  // Check if the range is valid: 
  // 1. Both are digits and start <= end
  // 2. Both are uppercase letters and start <= end
  // 3. Both are lowercase letters and start <= end
  if ( 
      (start >= '0' && start <= '9' && end >= '0' && end <= '9' && start <= end) ||
      (start >= 'A' && start <= 'Z' && end >= 'A' && end <= 'Z' && start <= end) ||
      (start >= 'a' && start <= 'z' && end >= 'a' && end <= 'z' && start <= end)
     )
  {
    // Fill the expanded array with characters from start to end
    while (start <= end)
    {
      expanded[i++] = start++;
    }
    expanded[i] = '\0'; // Null-terminate the string
  }
}