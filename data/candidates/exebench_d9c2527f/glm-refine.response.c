const char *__cdecl get_word(const char *str, int *len)
{
  const char *p = str;
  int i = 0;

  if (str)
  {
    // Skip leading dashes ('-')
    while (*p == '-')
      ++p;

    // Proceed only if the first character is a lowercase letter ('a'-'z')
    if (*p >= 'a' && *p <= 'z')
    {
      while (i < 64)
      {
        char c = p[i];
        bool is_valid = false;

        // Check if the character is a digit ('0'-'9')
        if (c >= '0' && c <= '9')
        {
          is_valid = true;
        }
        // Check if the character is a lowercase letter ('a'-'z')
        else if (c >= 'a' && c <= 'z')
        {
          is_valid = true;
        }
        // Check if the character is a dash ('-') or an underscore ('_')
        else if (c == '-' || c == '_')
        {
          is_valid = true;
        }

        if (!is_valid)
          break;
        ++i;
      }
    }
  }

  *len = i;
  return p;
}