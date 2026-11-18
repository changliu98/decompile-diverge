void __cdecl remove_vowels(char *text)
{
  char *read_ptr = text;
  char *write_ptr = text;

  while (*read_ptr)
  {
    // If the current character is not a vowel, copy it to the write position
    if (!strchr("AEIOUaeiou", *read_ptr))
    {
      *write_ptr = *read_ptr;
      write_ptr++;
    }
    read_ptr++;
  }
  
  // Null-terminate the modified string
  *write_ptr = '\0';
}