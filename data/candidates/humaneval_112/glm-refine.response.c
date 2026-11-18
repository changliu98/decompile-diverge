void __cdecl func0(const char *s, const char *c, char *result, char *palindrome)
{
  size_t len = strlen(s);
  char *filtered_str = (char *)malloc(len + 1);
  size_t filtered_idx = 0;

  // Filter out characters present in string 'c'
  for (size_t i = 0; s[i] != '\0'; ++i)
  {
    bool is_excluded = false;
    for (const char *p = c; *p != '\0'; ++p)
    {
      if (s[i] == *p)
      {
        is_excluded = true;
        break;
      }
    }
    
    if (!is_excluded)
    {
      filtered_str[filtered_idx++] = s[i];
    }
  }
  filtered_str[filtered_idx] = '\0';

  // Check if the filtered string is a palindrome
  size_t filtered_len = strlen(filtered_str);
  bool is_palindrome = true;
  for (size_t i = 0; i < filtered_len / 2; ++i)
  {
    if (filtered_str[i] != filtered_str[filtered_len - 1 - i])
    {
      is_palindrome = false;
      break;
    }
  }

  // Output results
  strcpy(result, filtered_str);
  strcpy(palindrome, is_palindrome ? "True" : "False");

  free(filtered_str);
}