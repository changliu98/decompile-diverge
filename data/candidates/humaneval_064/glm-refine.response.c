int __cdecl count_vowels_and_trailing_y(const char *str)
{
  int i;
  int len;
  int count = 0;

  len = strlen(str);
  
  // Count standard vowels (case-insensitive)
  for (i = 0; i < len; ++i)
  {
    if (strchr("aeiouAEIOU", str[i]))
    {
      ++count;
    }
  }

  // If the string is not empty and ends with 'y' or 'Y', count it as well
  if (len > 0 && (str[len - 1] == 'y' || str[len - 1] == 'Y'))
  {
    ++count;
  }

  return count;
}