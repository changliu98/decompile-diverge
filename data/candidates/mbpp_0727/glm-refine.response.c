char *__cdecl func0(const char *str)
{
  int i;
  int valid_char_count = 0;

  // Iterate through each character of the input string until the null terminator
  for ( i = 0; i < strlen(str); ++i )
  {
    // In glibc, __ctype_b_loc() returns a pointer to a table of character attributes.
    // The bitmask 8 corresponds to the _ISprint flag (printable characters).
    if ( isprint((unsigned char)str[i]) )
    {
      // Store the printable character in the global buffer and increment the index
      func0_result[valid_char_count++] = str[i];
    }
  }
  
  // Null-terminate the filtered string
  func0_result[valid_char_count] = '\0';
  
  return func0_result;
}