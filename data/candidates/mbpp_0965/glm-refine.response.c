char *__cdecl func0(const char *text)
{
  int i = 0;
  int j = 0;

  while (text[i])
  {
    // Check if the character is alphanumeric (matches _ISalnum flag 0x100 in glibc)
    if (isalnum((unsigned char)text[i]))
    {
      // If not the first character, and the previous character is a space (0x200) or punctuation (0x800)
      if (i > 0 && (isspace((unsigned char)text[i - 1]) || ispunct((unsigned char)text[i - 1])))
      {
        func0_buffer[j++] = '_';
      }
      func0_buffer[j++] = tolower((unsigned char)text[i]);
    }
    else
    {
      // Keep non-alphanumeric characters as-is
      func0_buffer[j++] = text[i];
    }
    i++;
  }
  
  func0_buffer[j] = '\0';
  return func0_buffer;
}