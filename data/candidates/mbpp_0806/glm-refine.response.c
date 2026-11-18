int __cdecl func0(const char *str)
{
  int length = strlen(str);
  int max_len = 0;
  int current_len = 0;

  for (int i = 0; i < length; ++i)
  {
    // __ctype_b_loc()[c] & 0x100 checks if the character is an uppercase letter (isupper)
    if (isupper(str[i]))
    {
      ++current_len;
    }
    else
    {
      if (current_len > max_len)
        max_len = current_len;
      current_len = 0;
    }
  }

  // Evaluate the final sequence if the string ends with an uppercase letter
  if (length > 0 && isupper(str[length - 1]) && current_len > max_len)
    return current_len;

  return max_len;
}