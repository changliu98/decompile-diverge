void __cdecl squeeze(char *s1, const char *s2)
{
  unsigned int i = 0;
  unsigned int j = 0;

  // Iterate through the source string s1
  while (s1[j])
  {
    unsigned int k = 0;
    
    // Check if the current character s1[j] exists in s2
    while (s2[k] && s1[j] != s2[k])
      ++k;

    // If we reached the end of s2, the character was not found
    if (!s2[k])
    {
      s1[i] = s1[j];
      ++i;
    }
    ++j;
  }
  
  // Null-terminate the modified string
  s1[i] = 0;
}