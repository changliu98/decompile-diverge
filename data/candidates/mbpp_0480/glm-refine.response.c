char __cdecl func0(const char *str)
{
  int counts[256] = {0};
  int max_count = -1;
  char max_char = 0;
  int length = strlen(str);

  // Count the frequency of each character in the string
  for (int i = 0; i < length; ++i)
  {
    ++counts[(unsigned char)str[i]];
  }

  // Find the character with the maximum frequency
  for (int i = 0; i < length; ++i)
  {
    if (max_count < counts[(unsigned char)str[i]])
    {
      max_count = counts[(unsigned char)str[i]];
      max_char = str[i];
    }
  }

  return max_char;
}