void __cdecl remove_all_chars(char *str, char c)
{
  char *pr = str; // read pointer
  char *pw = str; // write pointer

  while (*pr)
  {
    char current_char = *pr++;
    *pw = current_char;
    
    // Advance the write pointer only if the character is not the one being removed
    if (current_char != c)
      pw++;
  }
  
  // Null-terminate the modified string
  *pw = '\0';
}