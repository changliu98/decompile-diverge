int __cdecl func0(const char *str)
{
  int last_word_len = 0;
  
  // Skip leading spaces
  while (*str == ' ')
    ++str;

  // Iterate through the remaining string
  for (size_t i = 0; i < strlen(str); ++i)
  {
    if (str[i] == ' ')
      last_word_len = 0;
    else
      ++last_word_len;
  }
  
  return last_word_len;
}