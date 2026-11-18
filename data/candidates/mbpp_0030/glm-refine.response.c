int __cdecl func0(char *s)
{
  int count = 0;
  int len = strlen(s);
  
  // Iterate over all possible starting indices for substrings
  for (int start = 0; start < len; ++start)
  {
    // Iterate over all possible lengths for the substring starting at 'start'
    // The maximum length is bounded by the remaining characters in the string (len - start)
    for (int sub_len = 1; sub_len <= len - start; ++sub_len)
    {
      // If the substring meets the condition, increment the counter
      if (check_Equality(s, start, sub_len))
      {
        ++count;
      }
    }
  }
  
  return count;
}