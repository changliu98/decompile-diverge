void __cdecl squeeze_all(char *s, char *b)
{
  int write_idx = 0;
  char is_bad_char;
  int j;

  for (int i = 0; s[i] != '\0'; ++i)
  {
    is_bad_char = 0;
    
    // Check if the current character exists in the string 'b'
    for (j = 0; b[j] != '\0'; ++j)
    {
      if (s[i] == b[j])
      {
        is_bad_char = 1;
      }
    }

    // If the character is not in 'b', keep it in the string
    if (!is_bad_char)
    {
      s[write_idx++] = s[i];
    }
  }
  
  // Null-terminate the squeezed string
  s[write_idx] = '\0';
}