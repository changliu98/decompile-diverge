int __cdecl func0(const char *text)
{
  int len = strlen(text);
  const char *ptr = text;

  // Skip leading spaces
  while (*ptr == ' ')
  {
    ++ptr;
    --len;
  }

  // Return -1 if the string is empty or contained only spaces
  if (len < 1)
    return -1;

  // Determine starting index based on the presence of a sign (+ or -)
  int start = 0;
  if (*ptr == '+' || *ptr == '-')
  {
    start = 1;
  }

  // Check if the remaining characters are all digits
  for (int i = start; i < len; ++i)
  {
    if (ptr[i] < '0' || ptr[i] > '9')
      return 0;
  }

  return 1;
}