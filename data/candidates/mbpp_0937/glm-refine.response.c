char __cdecl func0(const char *str)
{
  int frequency[256] = {0};
  int max_freq = 0;
  char max_char = 0;
  size_t len = strlen(str);

  for (size_t i = 0; i < len; ++i)
  {
    unsigned char current_char = (unsigned char)str[i];
    
    if (++frequency[current_char] > max_freq)
    {
      max_freq = frequency[current_char];
      max_char = str[i];
    }
  }
  
  return max_char;
}