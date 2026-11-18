void __cdecl string_rip(char *str, const char *ripper)
{
  char *t_ptr = str;
  const char *stra = str;
  const char *ripper_idx;

  // Iterate over each character in the input string
  while (*stra)
  {
    ripper_idx = ripper;
    
    // Check if the current character exists in the 'ripper' string
    while (*ripper_idx)
    {
      if (*stra == *ripper_idx)
        break; // Character should be stripped
      ++ripper_idx;
    }

    // If the character was not found in 'ripper', keep it
    if (!*ripper_idx)
    {
      *t_ptr++ = *stra;
    }
    
    ++stra;
  }
  
  // Null-terminate the modified string
  *t_ptr = '\0';
}