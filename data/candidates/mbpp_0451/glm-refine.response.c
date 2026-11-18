char *__cdecl func0(char *str)
{
  int write_idx = 0;
  int read_idx = 0;

  // Iterate through the string until the null terminator is reached
  while (str[read_idx])
  {
    // Check if the current character is NOT a space
    // 0x2000 corresponds to the _ISspace flag in glibc's __ctype_b_loc table
    if (!isspace((unsigned char)str[read_idx]))
    {
      // Keep the character by copying it to the write position
      str[write_idx] = str[read_idx];
      write_idx++;
    }
    read_idx++;
  }
  
  // Null-terminate the modified string
  str[write_idx] = '\0';
  
  return str;
}